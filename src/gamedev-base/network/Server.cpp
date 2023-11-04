//
// Created by robin on 03.11.23.
//

#include "Server.h"

namespace ggj
{
    static Server *callbackInstance; //TODO: Find a cleaner solution than using a static instance
    static void SteamNetConnectionStatusChangedCallback( SteamNetConnectionStatusChangedCallback_t *pInfo )
    {
        callbackInstance->onSteamNetConnectionStatusChanged( pInfo );
    }
    
    // trim from start (in place)
    static inline void ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
            return !std::isspace(ch);
        }));
    }

    // trim from end (in place)
    static inline void rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
            return !std::isspace(ch);
        }).base(), s.end());
    }
    
    void Server::run()
    {
        // Select instance to use.  For now we'll always use the default.
        // But we could use SteamGameServerNetworkingSockets() on Steam.
        m_netInterface = SteamNetworkingSockets();
        
        uint16_t port = m_info.getPort();
        std::string name = m_info.getName();
        
        // Start listening
        SteamNetworkingIPAddr serverLocalAddr;
        serverLocalAddr.Clear();
        serverLocalAddr.m_port = port;
        SteamNetworkingConfigValue_t opt;
        
        //TODO: set callback
        opt.SetPtr( k_ESteamNetworkingConfig_Callback_ConnectionStatusChanged, (void*)SteamNetConnectionStatusChangedCallback );
        m_listenSocket = m_netInterface->CreateListenSocketIP( serverLocalAddr, 1, &opt );
        
        if ( m_listenSocket == k_HSteamListenSocket_Invalid )
            m_logger.error(fmt::format("Failed to listen on port {0}", port));
        
        m_pollGroup = m_netInterface->CreatePollGroup();
        
        if ( m_pollGroup == k_HSteamNetPollGroup_Invalid )
            m_logger.error(fmt::format("Failed to listen on port {0}", port));
        
        m_logger.information(fmt::format("Server listening on port {0}", port));
        m_logger.information(fmt::format("Server local IP: {0}", m_info.getIpAddress().getLocalIp()));
        m_logger.information(fmt::format("Server public IP: {0}", m_info.getIpAddress().getPublicIp()));
        m_logger.information(fmt::format("Server name: {0}", name ));
        
        while ( !m_quit )
        {
            pollIncomingMessages();
            pollConnectionStateChanges();
            pollLocalUserInput();
            std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
        }
        
        // Close all the connections
        m_logger.information( "Closing connections...\n" );
        for ( auto it: m_mapClients )
        {
            // Send them one more goodbye message.  Note that we also have the
            // connection close reason as a place to send final data.  However,
            // that's usually best left for more diagnostic/debug text not actual
            // protocol strings.
            sendStringToClient( it.first, "Server is shutting down.  Goodbye." );
            
            // Close the connection.  We use "linger mode" to ask SteamNetworkingSockets
            // to flush this out and close gracefully.
            m_netInterface->CloseConnection( it.first, 0, "Server Shutdown", true );
        }
        m_mapClients.clear();
        
        m_netInterface->CloseListenSocket( m_listenSocket );
        m_listenSocket = k_HSteamListenSocket_Invalid;
        
        m_netInterface->DestroyPollGroup( m_pollGroup );
        m_pollGroup = k_HSteamNetPollGroup_Invalid;
    }
    
    void Server::stop()
    {
        m_quit = true;
        
        // Give connections time to finish up.  This is an application layer protocol
        // here, it's not TCP.  Note that if you have an application and you need to be
        // more sure about cleanup, you won't be able to do this.  You will need to send
        // a message and then either wait for the peer to close the connection, or
        // you can pool the connection to see if any reliable data is pending.
        std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );
        
#ifdef STEAMNETWORKINGSOCKETS_OPENSOURCE
        GameNetworkingSockets_Kill();
#else
        SteamDatagramClient_Kill();
#endif
    }
    
    void Server::pollIncomingMessages()
    {
        char temp[ 1024 ];
        
        while ( !m_quit )
        {
            ISteamNetworkingMessage *incomingMsg = nullptr;
            int numMsgs = m_netInterface->ReceiveMessagesOnPollGroup(m_pollGroup, &incomingMsg, 1 );
            if ( numMsgs == 0 )
                break;
            if ( numMsgs < 0 )
                m_logger.error(fmt::format("Error checking for messages"));
            //assert( numMsgs == 1 && pIncomingMsg );
            auto itClient = m_mapClients.find(incomingMsg->m_conn );
            //assert( itClient != m_mapClients.end() );
            
            // '\0'-terminate it to make it easier to parse
            std::string sCmd;
            sCmd.assign((const char *)incomingMsg->m_pData, incomingMsg->m_cbSize );
            const char *cmd = sCmd.c_str();
            
            // We don't need this anymore.
            incomingMsg->Release();
            
            // Check for known commands.  None of this example code is secure or robust.
            // Don't write a real server like this, please.
            
            if ( strncmp( cmd, "/nick", 5 ) == 0 )
            {
                const char *nick = cmd+5;
                while ( isspace(*nick) )
                    ++nick;
                
                // Let everybody else know they changed their name
                sprintf( temp, "%s shall henceforth be known as %s", itClient->second.nick.c_str(), nick );
                sendStringToAllClients( temp, itClient->first );
                
                // Respond to client
                sprintf( temp, "Ye shall henceforth be known as %s", nick );
                sendStringToClient( itClient->first, temp );
                
                // Actually change their name
                setClientNick( itClient->first, nick );
                continue;
            }
            
            // Assume it's just a ordinary chat message, dispatch to everybody else
            sprintf( temp, "%s: %s", itClient->second.nick.c_str(), cmd );
            sendStringToAllClients( temp, itClient->first );
        }
    }
    
    void Server::sendStringToClient(HSteamNetConnection conn, const char *str)
    {
        m_netInterface->SendMessageToConnection( conn, str, (uint32)strlen(str), k_nSteamNetworkingSend_Reliable, nullptr );
    }
    
    void Server::sendStringToAllClients(const char *str, HSteamNetConnection except)
    {
        for ( auto &c: m_mapClients )
        {
            if ( c.first != except )
                sendStringToClient( c.first, str );
        }
    }
    
    void Server::setClientNick(HSteamNetConnection conn, const std::string &nick)
    {
        // Remember their nick
        m_mapClients[conn].nick = nick;
        
        // Set the connection name, too, which is useful for debugging
        m_netInterface->SetConnectionName( conn, nick.c_str() );
    }
    
    void Server::pollConnectionStateChanges()
    {
        callbackInstance = this;
        m_netInterface->RunCallbacks();
    }
    
    void Server::pollLocalUserInput()
    {
        std::string cmd;
        while (!m_quit && localUserInputGetNext(cmd))
        {
            if ( strcmp( cmd.c_str(), "/quit" ) == 0 )
            {
                m_quit = true;
                m_logger.information("Shutting down server");
                break;
            }
            
            // That's the only command we support
            m_logger.information("The server only knows one command: '/quit'");
        }
    }
    
    bool Server::localUserInputGetNext(std::string &result)
    {
        bool got_input = false;
        m_mutexUserInputQueue.lock();
        while (!m_queueUserInput.empty() && !got_input )
        {
            result = m_queueUserInput.front();
            m_queueUserInput.pop();
            ltrim(result);
            rtrim(result);
            got_input = !result.empty(); // ignore blank lines
        }
        m_mutexUserInputQueue.unlock();
        return got_input;
    }
    
    void Server::onSteamNetConnectionStatusChanged(SteamNetConnectionStatusChangedCallback_t *pInfo)
    {
        char temp[1024];
        
        // What's the state of the connection?
        switch ( pInfo->m_info.m_eState )
        {
            case k_ESteamNetworkingConnectionState_None:
                // NOTE: We will get callbacks here when we destroy connections.  You can ignore these.
                break;
            
            case k_ESteamNetworkingConnectionState_ClosedByPeer:
            case k_ESteamNetworkingConnectionState_ProblemDetectedLocally:
            {
                // Ignore if they were not previously connected.  (If they disconnected
                // before we accepted the connection.)
                if ( pInfo->m_eOldState == k_ESteamNetworkingConnectionState_Connected )
                {
                    
                    // Locate the client.  Note that it should have been found, because this
                    // is the only codepath where we remove clients (except on shutdown),
                    // and connection change callbacks are dispatched in queue order.
                    auto itClient = m_mapClients.find( pInfo->m_hConn );
                    //assert( itClient != m_mapClients.end() );
                    
                    // Select appropriate log messages
                    const char *pszDebugLogAction;
                    if ( pInfo->m_info.m_eState == k_ESteamNetworkingConnectionState_ProblemDetectedLocally )
                    {
                        pszDebugLogAction = "problem detected locally";
                        sprintf( temp, "Alas, %s hath fallen into shadow.  (%s)", itClient->second.nick.c_str(),
                                 pInfo->m_info.m_szEndDebug );
                    }
                    else
                    {
                        // Note that here we could check the reason code to see if
                        // it was a "usual" connection or an "unusual" one.
                        pszDebugLogAction = "closed by peer";
                        sprintf( temp, "%s hath departed", itClient->second.nick.c_str() );
                    }
                    
                    // Spew something to our own log.  Note that because we put their nick
                    // as the connection description, it will show up, along with their
                    // transport-specific data (e.g. their IP address)
                    m_logger.information(fmt::format("Connection {0} {1}, reason {2}: {3}\n",
                            pInfo->m_info.m_szConnectionDescription,
                            pszDebugLogAction,
                            pInfo->m_info.m_eEndReason,
                            pInfo->m_info.m_szEndDebug
                    ));
                    
                    m_mapClients.erase( itClient );
                    
                    // Send a message so everybody else knows what happened
                    sendStringToAllClients( temp );
                }
                else
                {
                    //assert( pInfo->m_eOldState == k_ESteamNetworkingConnectionState_Connecting );
                }
                
                // Clean up the connection.  This is important!
                // The connection is "closed" in the network sense, but
                // it has not been destroyed.  We must close it on our end, too
                // to finish up.  The reason information do not matter in this case,
                // and we cannot linger because it's already closed on the other end,
                // so we just pass 0's.
                m_netInterface->CloseConnection( pInfo->m_hConn, 0, nullptr, false );
                break;
            }
            
            case k_ESteamNetworkingConnectionState_Connecting:
            {
                // This must be a new connection
                //assert( m_mapClients.find( pInfo->m_hConn ) == m_mapClients.end() );
                
                m_logger.information(fmt::format("Connection request from {0}", pInfo->m_info.m_szConnectionDescription));
                
                // A client is attempting to connect
                // Try to accept the connection.
                if ( m_netInterface->AcceptConnection( pInfo->m_hConn ) != k_EResultOK )
                {
                    // This could fail.  If the remote host tried to connect, but then
                    // disconnected, the connection may already be half closed.  Just
                    // destroy whatever we have on our side.
                    m_netInterface->CloseConnection( pInfo->m_hConn, 0, nullptr, false );
                    m_logger.information(fmt::format("Can't accept connection.  (It was already closed?)"));
                    break;
                }
                
                // Assign the poll group
                if ( !m_netInterface->SetConnectionPollGroup( pInfo->m_hConn, m_pollGroup ) )
                {
                    m_netInterface->CloseConnection( pInfo->m_hConn, 0, nullptr, false );
                    m_logger.information(fmt::format("Failed to set poll group?"));
                    break;
                }
                
                // Generate a random nick.  A random temporary nick
                // is really dumb and not how you would write a real chat server.
                // You would want them to have some sort of signon message,
                // and you would keep their client in a state of limbo (connected,
                // but not logged on) until them.  I'm trying to keep this example
                // code really simple.
                char nick[ 64 ];
                sprintf( nick, "GalderLover%d", 10000 + ( rand() % 100000 ) );
                
                // Send them a welcome message
                sprintf( temp, "Welcome, stranger.  Thou art known to us for now as '%s'; upon thine command '/nick' we shall know thee otherwise.", nick );
                sendStringToClient( pInfo->m_hConn, temp );
                
                // Also send them a list of everybody who is already connected
                if ( m_mapClients.empty() )
                {
                    sendStringToClient( pInfo->m_hConn, "Thou art utterly alone." );
                }
                else
                {
                    sprintf( temp, "%d companions greet you:", (int)m_mapClients.size() );
                    for ( auto &c: m_mapClients )
                        sendStringToClient( pInfo->m_hConn, c.second.nick.c_str() );
                }
                
                // Let everybody else know who they are for now
                sprintf( temp, "Hark!  A stranger hath joined this merry host.  For now we shall call them '%s'", nick );
                sendStringToAllClients( temp, pInfo->m_hConn );
                
                // Add them to the client list, using std::map wacky syntax
                m_mapClients[ pInfo->m_hConn ];
                setClientNick( pInfo->m_hConn, nick );
                break;
            }
            
            case k_ESteamNetworkingConnectionState_Connected:
                // We will get a callback immediately after accepting the connection.
                // Since we are the server, we can ignore this, it's not news to us.
                break;
            
            default:
                // Silences -Wswitch
                break;
        }
    }
    bool Server::initialize(uint16_t port, const std::string &name)
    {
        std::string localIp = m_resolver.getLocalIpAddress();
        std::string publicIp = m_resolver.getPublicIpAddress();
        m_info = {port, {localIp, publicIp}, name};
        
        SteamDatagramErrMsg errMsg;
        if (!GameNetworkingSockets_Init( nullptr, errMsg ))
        {
            m_logger.critical(fmt::format("GameNetworkingSockets_Init failed.  {0}", errMsg));
            return false;
        }
        return true;
    }
    
} // ggj
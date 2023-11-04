//
// Created by robin on 03.11.23.
//

#include "Client.h"

namespace ggj
{
    template<class TClientData, class TServerData>
    static Client<TClientData, TServerData> *callbackInstance;
    
    template<class TClientData, class TServerData>
    static void SteamNetConnectionStatusChangedCallback( SteamNetConnectionStatusChangedCallback_t *pInfo )
    {
        callbackInstance<TClientData, TServerData>->onSteamNetConnectionStatusChanged(pInfo);
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
    
    template<class TClientData, class TServerData>
    void Client<TClientData, TServerData>::connect(uint16_t port, std::string ipAddress)
    {
        // Select instance to use.  For now we'll always use the default.
        m_netInterface = SteamNetworkingSockets();
        
        SteamNetworkingIPAddr serverAddr {};
        std::string addr = fmt::format("{0}:{1}", ipAddress, port);
        serverAddr.ParseString(addr.c_str());
        
        // Start connecting
        char szAddr[ SteamNetworkingIPAddr::k_cchMaxString ];
        serverAddr.ToString( szAddr, sizeof(szAddr), true );
        m_logger.information(fmt::format("Connecting to chat server at {0}", szAddr));
        SteamNetworkingConfigValue_t opt;
        opt.SetPtr( k_ESteamNetworkingConfig_Callback_ConnectionStatusChanged, (void*)SteamNetConnectionStatusChangedCallback );
        m_connection = m_netInterface->ConnectByIPAddress( serverAddr, 1, &opt );
        if ( m_connection == k_HSteamNetConnection_Invalid )
            m_logger.critical(fmt::format("Failed to create connection"));
        
        while ( !m_quit )
        {
            pollIncomingMessages();
            pollConnectionStateChanges();
            pollLocalUserInput();
            std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
        }
    }
    
    template<class TClientData, class TServerData>
    ServerHostInfo Client<TClientData, TServerData>::getServerInfo() const
    {
        return {};
    }
    
    template<class TClientData, class TServerData>
    void Client<TClientData, TServerData>::ping() const
    {
    
    }
    
    template<class TClientData, class TServerData>
    void Client<TClientData, TServerData>::disconnect() const
    {
    
    }
    
    template<class TClientData, class TServerData>
    void Client<TClientData, TServerData>::onSteamNetConnectionStatusChanged(SteamNetConnectionStatusChangedCallback_t *pInfo)
    {
        //assert( pInfo->m_hConn == m_connection || m_connection == k_HSteamNetConnection_Invalid );
        
        // What's the state of the connection?
        switch ( pInfo->m_info.m_eState )
        {
            case k_ESteamNetworkingConnectionState_None:
                // NOTE: We will get callbacks here when we destroy connections.  You can ignore these.
                break;
            
            case k_ESteamNetworkingConnectionState_ClosedByPeer:
            case k_ESteamNetworkingConnectionState_ProblemDetectedLocally:
            {
                m_quit = true;
                
                // Print an appropriate message
                if ( pInfo->m_eOldState == k_ESteamNetworkingConnectionState_Connecting )
                {
                    // Note: we could distinguish between a timeout, a rejected connection,
                    // or some other transport problem.
                    m_logger.information(fmt::format( "We sought the remote host, yet our efforts were met with defeat.  ({0})", pInfo->m_info.m_szEndDebug ));
                }
                else if ( pInfo->m_info.m_eState == k_ESteamNetworkingConnectionState_ProblemDetectedLocally )
                {
                    m_logger.information(fmt::format( "Alas, troubles beset us; we have lost contact with the host.  ({0})", pInfo->m_info.m_szEndDebug ));
                }
                else
                {
                    // NOTE: We could check the reason code for a normal disconnection
                    m_logger.information(fmt::format( "The host hath bidden us farewell.  ({0})", pInfo->m_info.m_szEndDebug ));
                }
                
                // Clean up the connection.  This is important!
                // The connection is "closed" in the network sense, but
                // it has not been destroyed.  We must close it on our end, too
                // to finish up.  The reason information do not matter in this case,
                // and we cannot linger because it's already closed on the other end,
                // so we just pass 0's.
                m_netInterface->CloseConnection( pInfo->m_hConn, 0, nullptr, false );
                m_connection = k_HSteamNetConnection_Invalid;
                break;
            }
            
            case k_ESteamNetworkingConnectionState_Connecting:
                // We will get this callback when we start connecting.
                // We can ignore this.
                break;
            
            case k_ESteamNetworkingConnectionState_Connected:
                m_logger.information(fmt::format( "Connected to server OK" ));
                break;
            
            default:
                // Silences -Wswitch
                break;
        }
    }
    
    template<class TClientData, class TServerData>
    void Client<TClientData, TServerData>::pollIncomingMessages()
    {
        while (!m_quit)
        {
            ISteamNetworkingMessage *incomingMsg = nullptr;
            int numMsgs = m_netInterface->ReceiveMessagesOnConnection(m_connection, &incomingMsg, 1 );
            if ( numMsgs == 0 )
                break;
            if ( numMsgs < 0 )
                m_logger.critical(fmt::format("Error checking for messages"));
            
            // Just echo anything we get from the server
            fwrite(incomingMsg->m_pData, 1, incomingMsg->m_cbSize, stdout );
            fputc( '\n', stdout );
            
            // We don't need this anymore.
            incomingMsg->Release();
        }
    }
    
    template<class TClientData, class TServerData>
    void Client<TClientData, TServerData>::pollConnectionStateChanges()
    {
        callbackInstance<TClientData, TServerData> = this;
        m_netInterface->RunCallbacks();
    }
    
    template<class TClientData, class TServerData>
    void Client<TClientData, TServerData>::pollLocalUserInput()
    {
        std::string cmd;
        while ( !m_quit && localUserInputGetNext( cmd ))
        {
            
            // Check for known commands
            if ( strcmp( cmd.c_str(), "/quit" ) == 0 )
            {
                m_quit = true;
                m_logger.information(fmt::format("Disconnecting from chat server"));
                
                // Close the connection gracefully.
                // We use linger mode to ask for any remaining reliable data
                // to be flushed out.  But remember this is an application
                // protocol on UDP.  See ShutdownSteamDatagramConnectionSockets
                m_netInterface->CloseConnection( m_connection, 0, "Goodbye", true );
                break;
            }
            
            // Anything else, just send it to the server and let them parse it
            m_netInterface->SendMessageToConnection( m_connection, cmd.c_str(), (uint32)cmd.length(),
                                                     k_nSteamNetworkingSend_Reliable, nullptr );
        }
    }
    
    template<class TClientData, class TServerData>
    bool Client<TClientData, TServerData>::localUserInputGetNext(std::string &result)
    {
        bool got_input = false;
        m_mutexUserInputQueue.lock();
        while ( !m_queueUserInput.empty() && !got_input )
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
    
    template<class TClientData, class TServerData>
    bool Client<TClientData, TServerData>::initialize()
    {
        SteamDatagramErrMsg errMsg;
        if (!GameNetworkingSockets_Init( nullptr, errMsg ))
        {
            m_logger.critical(fmt::format("GameNetworkingSockets_Init failed.  {0}", errMsg));
            return false;
        }
        return true;
    }
    
    template<class TClientData, class TServerData>
    bool Client<TClientData, TServerData>::send(const TClientData &data)
    {
        return false;
    }
    template<class TClientData, class TServerData>
    bool Client<TClientData, TServerData>::receive(const TServerData &data)
    {
        return false;
    }
} // ggj
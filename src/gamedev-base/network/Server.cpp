//
// Created by robin on 03.11.23.
//

#include "Server.h"

namespace ggj
{
    ServerHostInfo Server::run(uint16_t port, const std::string &name)
    {
        std::string localIp = m_resolver.getLocalIpAddress();
        std::string publicIp = m_resolver.getPublicIpAddress();
        
        m_info = {port, {localIp, publicIp}, name};
        
        // Select instance to use.  For now we'll always use the default.
        // But we could use SteamGameServerNetworkingSockets() on Steam.
        m_netInterface = SteamNetworkingSockets();
        
        // Start listening
        SteamNetworkingIPAddr serverLocalAddr;
        serverLocalAddr.Clear();
        serverLocalAddr.m_port = port;
        SteamNetworkingConfigValue_t opt;
        opt.SetPtr( k_ESteamNetworkingConfig_Callback_ConnectionStatusChanged, (void*)SteamNetConnectionStatusChangedCallback );
        m_listenSocket = m_netInterface->CreateListenSocketIP( serverLocalAddr, 1, &opt );
        if ( m_listenSocket == k_HSteamListenSocket_Invalid )
            FatalError( "Failed to listen on port %d", nPort );
        m_hPollGroup = m_netInterface->CreatePollGroup();
        if ( m_hPollGroup == k_HSteamNetPollGroup_Invalid )
            FatalError( "Failed to listen on port %d", nPort );
        Printf( "Server listening on port %d\n", nPort );
        
        while ( !g_bQuit )
        {
            PollIncomingMessages();
            PollConnectionStateChanges();
            PollLocalUserInput();
            std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
        }
        
        // Close all the connections
        Printf( "Closing connections...\n" );
        for ( auto it: m_mapClients )
        {
            // Send them one more goodbye message.  Note that we also have the
            // connection close reason as a place to send final data.  However,
            // that's usually best left for more diagnostic/debug text not actual
            // protocol strings.
            SendStringToClient( it.first, "Server is shutting down.  Goodbye." );
            
            // Close the connection.  We use "linger mode" to ask SteamNetworkingSockets
            // to flush this out and close gracefully.
            m_netInterface->CloseConnection( it.first, 0, "Server Shutdown", true );
        }
        m_mapClients.clear();
        
        m_netInterface->CloseListenSocket( m_listenSocket );
        m_listenSocket = k_HSteamListenSocket_Invalid;
        
        m_netInterface->DestroyPollGroup( m_hPollGroup );
        m_hPollGroup = k_HSteamNetPollGroup_Invalid;
        
        return m_info;
    }
    
    void Server::stop() const
    {
    
    }
} // ggj
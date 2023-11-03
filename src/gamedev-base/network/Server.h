//
// Created by robin on 03.11.23.
//

#ifndef GALDER_GAME_JAM_2023_PROJECT_SERVER_H
#define GALDER_GAME_JAM_2023_PROJECT_SERVER_H

#include "../interfaces/network/IServer.h"
#include "../interfaces/network/IIpAddressResolver.h"

#include <steam/steamnetworkingsockets.h>
#include <steam/isteamnetworkingutils.h>
#ifndef STEAMNETWORKINGSOCKETS_OPENSOURCE
#include <steam/steam_api.h>
#endif

namespace ggj
{
    
    class Server : public IServer
    {
        public:
            Server(IIpAddressResolver &ipAddressResolver) : m_resolver {ipAddressResolver}
            {
            
            }
            
            ServerHostInfo run(uint16_t port, const std::string &name) override;
            void stop() const override;
            
        private:
            IIpAddressResolver &m_resolver;
            ServerHostInfo m_info{};
            
            //Steam networking stuff
            HSteamListenSocket m_listenSocket;
            HSteamNetPollGroup m_pollGroup;
            ISteamNetworkingSockets *m_netInterface;
            std::map< HSteamNetConnection, Client_t > m_mapClients;
    };
    
} // ggj

#endif //GALDER_GAME_JAM_2023_PROJECT_SERVER_H

//
// Created by robin on 03.11.23.
//

#ifndef GALDER_GAME_JAM_2023_PROJECT_SERVER_H
#define GALDER_GAME_JAM_2023_PROJECT_SERVER_H

#include "../interfaces/system/ILogger.h"
#include "../interfaces/network/IServer.h"
#include "../interfaces/network/IIpAddressResolver.h"
#include "../data/ClientInfo.hpp"

#include <steam/steamnetworkingsockets.h>
#include <steam/isteamnetworkingutils.h>
#ifndef STEAMNETWORKINGSOCKETS_OPENSOURCE
#include <steam/steam_api.h>
#endif

#include <chrono>
#include <thread>
#include <mutex>
#include <map>
#include <queue>

namespace ggj
{
    
    class Server : public IServer
    {
        public:
            Server(ILogger &logger, IIpAddressResolver &ipAddressResolver) : m_logger {logger}, m_resolver {ipAddressResolver}
            {
            
            }
            void initialize(uint16_t port, const std::string &name) override;
            void run() override;
            void stop() override;
            
            void onSteamNetConnectionStatusChanged(SteamNetConnectionStatusChangedCallback_t *pInfo);
            
        private:
            ILogger &m_logger;
            IIpAddressResolver &m_resolver;
            ServerHostInfo m_info{};
            
            //Steam networking stuff
            HSteamListenSocket m_listenSocket;
            HSteamNetPollGroup m_pollGroup;
            ISteamNetworkingSockets *m_netInterface;
            std::map<HSteamNetConnection, ClientInfo> m_mapClients;
            std::mutex mutexUserInputQueue;
            std::queue< std::string > queueUserInput;
            std::thread *s_pThreadUserInput = nullptr;
            
            bool m_quit = false;
            
            void pollIncomingMessages();
            void sendStringToClient(HSteamNetConnection conn, const char *str);
            void sendStringToAllClients(const char *str, HSteamNetConnection except = k_HSteamNetConnection_Invalid);
            void setClientNick(HSteamNetConnection conn, const std::string &nick);
            void pollConnectionStateChanges();
            void pollLocalUserInput();
            bool localUserInputGetNext(std::string &result);
    };
    
} // ggj

#endif //GALDER_GAME_JAM_2023_PROJECT_SERVER_H

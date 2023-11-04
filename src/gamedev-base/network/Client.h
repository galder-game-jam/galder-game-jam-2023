//
// Created by robin on 03.11.23.
//

#ifndef GALDER_GAME_JAM_2023_PROJECT_CLIENT_H
#define GALDER_GAME_JAM_2023_PROJECT_CLIENT_H

#include "../interfaces/system/ILogger.h"
#include "../interfaces/network/IIpAddressResolver.h"
#include "../interfaces/network/IClient.h"
#include "fmt/format.h"

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
    
    class Client : public IClient
    {
        public:
            Client(ILogger &logger, IIpAddressResolver &ipAddressResolver) : m_logger {logger}, m_resolver {ipAddressResolver}
            {
            
            }
            bool initialize() override;
            void connect(uint16_t port, std::string ipAddress) override;
            [[nodiscard]] ServerHostInfo getServerInfo() const override;
            void ping() const override;
            void disconnect() const override;
            
            void onSteamNetConnectionStatusChanged(SteamNetConnectionStatusChangedCallback_t *pInfo);
            
        private:
            ILogger &m_logger;
            IIpAddressResolver &m_resolver;
            bool m_quit = false;
            
            //Steam network stuff
            ISteamNetworkingSockets *m_netInterface;
            HSteamNetConnection m_connection;
            std::mutex m_mutexUserInputQueue;
            std::queue< std::string > m_queueUserInput;
            //std::thread *m_threadUserInput = nullptr;
            
            void pollIncomingMessages();
            void pollConnectionStateChanges();
            void pollLocalUserInput();
            bool localUserInputGetNext(std::string &result);
    };
    
} // ggj

#endif //GALDER_GAME_JAM_2023_PROJECT_CLIENT_H

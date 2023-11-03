//
// Created by robin on 03.11.23.
//

#ifndef GALDER_GAME_JAM_2023_PROJECT_SERVER_H
#define GALDER_GAME_JAM_2023_PROJECT_SERVER_H

#include "../interfaces/network/IServer.h"
#include "../interfaces/network/IIpAddressResolver.h"

namespace ggj
{
    
    class Server : public IServer
    {
        public:
            Server(IIpAddressResolver &ipAddressResolver) : m_resolver {ipAddressResolver}
            {
            
            }
            
            ServerHostInfo run(uint16_t port, const std::string &name) const override;
            void stop() const override;
            
        private:
            IIpAddressResolver &m_resolver;
    };
    
} // ggj

#endif //GALDER_GAME_JAM_2023_PROJECT_SERVER_H

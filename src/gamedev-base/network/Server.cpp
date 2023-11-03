//
// Created by robin on 03.11.23.
//

#include "Server.h"

namespace ggj
{
    ServerHostInfo Server::run(uint16_t port, const std::string &name) const
    {
        std::string localIp = m_resolver.getLocalIpAddress();
        std::string publicIp = m_resolver.getPublicIpAddress();
        return {port, {localIp, publicIp}, name};
    }
    
    void Server::stop() const
    {
    
    }
} // ggj
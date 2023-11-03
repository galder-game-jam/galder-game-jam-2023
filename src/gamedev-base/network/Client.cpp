//
// Created by robin on 03.11.23.
//

#include "Client.h"

namespace ggj
{
    ConnectionStatus Client::connect(uint16_t port) const
    {
        return ConnectionStatus::None;
    }
    
    ServerHostInfo Client::getServerInfo() const
    {
        return {};
    }
    
    void Client::ping() const
    {
    
    }
    
    void Client::disconnect() const
    {
    
    }
} // ggj
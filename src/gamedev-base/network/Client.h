//
// Created by robin on 03.11.23.
//

#ifndef GALDER_GAME_JAM_2023_PROJECT_CLIENT_H
#define GALDER_GAME_JAM_2023_PROJECT_CLIENT_H

#include "../interfaces/network/IClient.h"

namespace ggj
{
    
    class Client : public IClient
    {
        public:
            ConnectionStatus connect(uint16_t port) const override;
            ServerHostInfo getServerInfo() const override;
            void ping() const override;
            void disconnect() const override;
    };
    
} // ggj

#endif //GALDER_GAME_JAM_2023_PROJECT_CLIENT_H

//
// Created by robin on 04.11.23.
//

#ifndef GALDER_GAME_JAM_2023_PROJECT_GALDERSERVER_H
#define GALDER_GAME_JAM_2023_PROJECT_GALDERSERVER_H

#include "../../gamedev-base/GameDevBase.h"
#include "../data/PlayerNetworkData.hpp"
#include "../data/ServerNetworkData.hpp"

namespace ggj
{
    
    class GalderServer : ggj::Server<ServerNetworkData, PlayerNetworkData>
    {
        public:
            GalderServer(ILogger &logger, IIpAddressResolver &ipAddressResolver) :
                    ggj::Server<ServerNetworkData, PlayerNetworkData>(logger, ipAddressResolver)
            {
            
            }
    };
    
} // ggj

#endif //GALDER_GAME_JAM_2023_PROJECT_GALDERSERVER_H

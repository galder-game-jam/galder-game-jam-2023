//
// Created by robin on 04.11.23.
//

#ifndef GALDER_GAME_JAM_2023_PROJECT_GALDERCLIENT_H
#define GALDER_GAME_JAM_2023_PROJECT_GALDERCLIENT_H

#include "../../gamedev-base/GameDevBase.h"
#include "../data/PlayerNetworkData.hpp"
#include "../data/ServerNetworkData.hpp"

namespace ggj
{
    
    class GalderClient : ggj::Client<PlayerNetworkData, ServerNetworkData>
    {
            GalderClient(ILogger &logger, IIpAddressResolver &ipAddressResolver) :
                    ggj::Client<PlayerNetworkData, ServerNetworkData>(logger, ipAddressResolver)
            {
                
            }
    };
    
} // ggj

#endif //GALDER_GAME_JAM_2023_PROJECT_GALDERCLIENT_H

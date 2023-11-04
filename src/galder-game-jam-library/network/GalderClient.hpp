//
// Created by robin on 04.11.23.
//

#ifndef GALDER_GAME_JAM_2023_PROJECT_GALDERCLIENT_HPP
#define GALDER_GAME_JAM_2023_PROJECT_GALDERCLIENT_HPP

#include "../../gamedev-base/GameDevBase.h"
#include "../data/PlayerNetworkData.hpp"
#include "../data/ServerNetworkData.hpp"

namespace ggj
{
    
    class GalderClient : public ggj::Client<PlayerNetworkData, ServerNetworkData>
    {
        public:
            GalderClient(ILogger &logger, IIpAddressResolver &ipAddressResolver) :
                    ggj::Client<PlayerNetworkData, ServerNetworkData>(logger, ipAddressResolver)
            {
            
            }
    };
    
} // ggj

#endif //GALDER_GAME_JAM_2023_PROJECT_GALDERCLIENT_HPP

//
// Created by robin on 04.11.23.
//

#ifndef GALDER_GAME_JAM_2023_PROJECT_SERVERNETWORKDATA_HPP
#define GALDER_GAME_JAM_2023_PROJECT_SERVERNETWORKDATA_HPP

#include <string>

namespace ggj
{
    class ServerNetworkData
    {
        public:
            bool isInvalid {true}; //0 = false, everything else is true.
            uint32_t id{}; //Just an ID sent
            char message[256];
    };
}

#endif //GALDER_GAME_JAM_2023_PROJECT_SERVERNETWORKDATA_HPP

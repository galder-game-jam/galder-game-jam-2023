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
            bool isValid {};
            std::string message {}; //Just sending a message, for now
    };
}

#endif //GALDER_GAME_JAM_2023_PROJECT_SERVERNETWORKDATA_HPP

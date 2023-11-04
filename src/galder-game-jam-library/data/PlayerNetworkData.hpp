//
// Created by robin on 04.11.23.
//

#ifndef GALDER_GAME_JAM_2023_PROJECT_PLAYERNETWORKDATA_HPP
#define GALDER_GAME_JAM_2023_PROJECT_PLAYERNETWORKDATA_HPP

#include "../../gamedev-base/GameDevBase.h"
#include "raylib-cpp.hpp"

namespace ggj
{
    class PlayerNetworkData
    {
        public:
            raylib::Vector2 position{}; //
            uint8_t action{0}; //
            uint8_t animationState{0}; //
            uint8_t animationFrame{0}; //
    };
}


#endif //GALDER_GAME_JAM_2023_PROJECT_PLAYERNETWORKDATA_HPP

//
// Created by robin on 03.11.23.
//

#ifndef GALDER_GAME_JAM_2023_PROJECT_ISERVER_H
#define GALDER_GAME_JAM_2023_PROJECT_ISERVER_H

#include <cstdint>
#include <string>
#include "../../data/ServerHostInfo.hpp"

namespace ggj
{
    class IServer
    {
        public:
            virtual ~IServer() noexcept = default;
            [[nodiscard]] virtual ServerHostInfo run(uint16_t port, const std::string& name ) const = 0;
            virtual void stop() const = 0;
    };
}

#endif //GALDER_GAME_JAM_2023_PROJECT_ISERVER_H

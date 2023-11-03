//
// Created by robin on 03.11.23.
//

#ifndef GALDER_GAME_JAM_2023_PROJECT_ICLIENT_H
#define GALDER_GAME_JAM_2023_PROJECT_ICLIENT_H

#include "../../enums/ConnectionStatus.h"
#include <cstdint>
namespace ggj
{
    class IClient
    {
        public:
            virtual ~IClient() noexcept = default;
            [[nodiscard]] virtual ConnectionStatus connect(uint16_t port) const = 0;
            virtual void ping() const = 0;
            virtual void disconnect() const = 0;
    };
}

#endif //GALDER_GAME_JAM_2023_PROJECT_ICLIENT_H

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
    template <class TServerData, class TClientData>
    class IServer
    {
        public:
            virtual ~IServer() noexcept = default;
            virtual bool initialize(uint16_t port, const std::string& name ) = 0;
            virtual void run() = 0;
            virtual void stop() = 0;
            
        protected:
            virtual bool send(const TServerData &data) = 0;
            virtual bool receive(const TClientData &data) = 0;
    };
}

#endif //GALDER_GAME_JAM_2023_PROJECT_ISERVER_H

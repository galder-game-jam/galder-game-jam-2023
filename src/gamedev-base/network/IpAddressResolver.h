//
// Created by robin on 03.11.23.
//

#ifndef GALDER_GAME_JAM_2023_PROJECT_IPADDRESSRESOLVER_H
#define GALDER_GAME_JAM_2023_PROJECT_IPADDRESSRESOLVER_H

#include "../interfaces/network/IIpAddressResolver.h"
#include "ipify.h"
namespace ggj
{
    class IpAddressResolver : public ggj::IIpAddressResolver
    {
        public:
            [[nodiscard]] std::string getLocalIpAddress() const override;
            [[nodiscard]] std::string getPublicIpAddress() const override;
    };
}

#endif //GALDER_GAME_JAM_2023_PROJECT_IPADDRESSRESOLVER_H

//
// Created by soberga on 12.11.22.
//

#ifndef GAME_DEV_TEMPLATE_ANIMATIONNAME_H
#define GAME_DEV_TEMPLATE_ANIMATIONNAME_H

namespace ggj
{

    enum class AnimationName
    {
        None = 0,
        PlayerIdle = 1,
        PlayerWalk = 2,
        PlayerJump = 3,
        PlayerFall = 4,
        EnemyBatMove = 5,
        EnemyBatDead = 6,
        EnemySnakeMove = 7,
        CoinSpin = 8,
        EnemySpiderWalk = 9,
        EnemyThingWalk = 10,
        EnemyGhostFly = 11,
        PortalIdle = 12,
        PortalActive = 13,
        PortalTeleport = 14,
        PortalClosing = 15,
        PortalClosed = 16,
        Player1Idle = 17,
        Player1Walk = 18,
        Player1Jump = 19,
        Player1Fall = 20,
    };

} // ggj

#endif //GAME_DEV_TEMPLATE_ANIMATIONNAME_H

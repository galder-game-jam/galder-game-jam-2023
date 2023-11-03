//
// Created by robin on 27.10.22.
//

#ifndef GAME_DEV_TEMPLATE_RESOURCENAME_H
#define GAME_DEV_TEMPLATE_RESOURCENAME_H

#include <cstdint>

namespace ggj
{
    /*!
     * ResourceName should be composed by something like this:
     * <ResourceType><ResourceId>.
     * Example:
     * GraphicsPlayer - Where <ResourceType>=Graphics and <ResourceId>=Player.
     *
     * ResourceTypes:
     * Graphics
     * Sound
     *
     */
    enum class ResourceName : uint16_t
    {
        None = 0,
        GraphicsPlayer = 1,
        MapProject = 7,
        GraphicsMagicCliffsTileset = 10,
        GraphicsEnemyBat = 11,
        GraphicsCrate = 12,
        GraphicsNinjaSmiley = 13,
        GraphicsJumpolini = 14,
        GraphicsGem1 = 15,
        GraphicsGem2 = 16,
        GraphicsGem3 = 17,
        GraphicsGem4 = 18,

        GraphicsBackground01MountainsGrass = 118,
        GraphicsBackground02MountainsDesert = 119,
        GraphicsBackground03MountainsSnow = 120,
        GraphicsBackground04CityNight = 121,
        GraphicsBackground05Graveyard = 122,
        GraphicsCharacterHudChar01 = 123,
        GraphicsCharacterHudChar02 = 124,
        GraphicsCharacterHudChar03 = 125,
        GraphicsCharacterHudChar04 = 126,
        GraphicsCharacterHudChar05 = 127,
        GraphicsCharacterHudChar06 = 128,
        GraphicsCharacterHudChar07 = 129,
        GraphicsCharacterHudChar08 = 130,
        GraphicsCharacterHudChar09 = 131,
        GraphicsCharacterHudChar10 = 132,
        GraphicsCharacterHudChar11 = 133,
        GraphicsCharacterHudChar12 = 134,
        GraphicsCharacterHudChar13 = 135,
        GraphicsCharacterHudChar14 = 136,
        GraphicsCharacterHudChar15 = 137,
        GraphicsCharacterHudChar16 = 138,
        GraphicsCharacterHudChar17 = 139,
        GraphicsCharacterHudChar18 = 140,
        GraphicsCharacterHudChar19 = 141,
        GraphicsCharacterHudChar20 = 142,
        GraphicsCharacterHudChar21 = 143,
        GraphicsCharacterHudChar22 = 144,
        GraphicsCharacterHudChar23 = 145,
        GraphicsCharacterHudChar24 = 146,
        GraphicsCharacterHudChar25 = 147,
        GraphicsEnemyGhostFlyingGhost1 = 148,
        GraphicsEnemyGhostFlyingGhost2 = 149,
        GraphicsEnemyGhostFlyingGhost3 = 150,
        GraphicsEnemyGhostFlyingGhost4 = 151,
        GraphicsEnemySpiderWalkSpider1 = 152,
        GraphicsEnemySpiderWalkSpider2 = 153,
        GraphicsEnemySpiderWalkSpider3 = 154,
        GraphicsEnemySpiderWalkSpider4 = 155,
        GraphicsEnemyThingWalkThing1 = 156,
        GraphicsEnemyThingWalkThing2 = 157,
        GraphicsEnemyThingWalkThing3 = 158,
        GraphicsEnemyThingWalkThing4 = 159,
        GraphicsExplosion1 = 160,
        GraphicsExplosion2 = 161,
        GraphicsExplosion3 = 162,
        GraphicsExplosion4 = 163,
        GraphicsExplosion5 = 164,
        GraphicsExplosion6 = 165,
        GraphicsHudUiBigPieces = 166,
        GraphicsMeleeSwoosh = 167,
        GraphicsPlayerSpritemapGreenpants = 168,
        GraphicsPlayerSpritemapGreypants = 169,
        GraphicsPlayerSpritemap = 170,
        GraphicsPlayerSpritemapRedpants = 171,
        GraphicsPowerupsRpgIcons = 172,
        GraphicsShootFireFire1 = 173,
        GraphicsShootFireFire2 = 174,
        GraphicsTilesJungleTerrain = 175,
        GraphicsTilesObjects = 176,
        GraphicsCoin = 177,
    };
}

#endif //GAME_DEV_TEMPLATE_RESOURCENAME_H

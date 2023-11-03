//
// Created by robin on 29.10.22.
//

#ifndef GAME_DEV_TEMPLATE_MAPPER_HPP
#define GAME_DEV_TEMPLATE_MAPPER_HPP

#include <map>
#include "../interfaces/system/IMapper.h"
#include "../enums/TextureName.h"
#include "../enums/ResourceName.h"

namespace ggj
{
    class Mapper : public IMapper
    {
        public:
            Mapper()
            {
                m_strToTex["characters.png"] = TextureName::Player;
                m_strToTex["sheet.png"] = TextureName::Tileset1;
                m_strToTex["tiles.png"] = TextureName::Tileset2;
                m_strToTex["boulder-small.png"] = TextureName::BoulderSmall;
                m_strToTex["andre.png"] = TextureName::Andre;
                m_strToTex["player-simple.png"] = TextureName::PlayerSimple;
                m_strToTex["magic-cliffs.png"] = TextureName::MagicCliffsTileset;
                m_strToTex["bat.png"] = TextureName::Bat;
                m_strToTex["crate.png"] = TextureName::Crate;
                m_strToTex["ninja.png"] = TextureName::NinjaSmiley;
                m_strToTex["jumpolini.png"] = TextureName::Jumpolini;
                m_strToTex["gem1.png"] = TextureName::Gem1;
                m_strToTex["gem2.png"] = TextureName::Gem2;
                m_strToTex["gem3.png"] = TextureName::Gem3;
                m_strToTex["gem4.png"] = TextureName::Gem4;

                m_strToTex["background01_mountains_grass.png"] = TextureName::Background01MountainsGrass;
                m_strToTex["background02_mountains_desert.png"] = TextureName::Background02MountainsDesert;
                m_strToTex["background03_mountains_snow.png"] = TextureName::Background03MountainsSnow;
                m_strToTex["background04_city_night.png"] = TextureName::Background04CityNight;
                m_strToTex["background05_graveyard.png"] = TextureName::Background05Graveyard;
                m_strToTex["char01.png"] = TextureName::CharacterHudChar01;
                m_strToTex["char02.png"] = TextureName::CharacterHudChar02;
                m_strToTex["char03.png"] = TextureName::CharacterHudChar03;
                m_strToTex["char04.png"] = TextureName::CharacterHudChar04;
                m_strToTex["char05.png"] = TextureName::CharacterHudChar05;
                m_strToTex["char06.png"] = TextureName::CharacterHudChar06;
                m_strToTex["char07.png"] = TextureName::CharacterHudChar07;
                m_strToTex["char08.png"] = TextureName::CharacterHudChar08;
                m_strToTex["char09.png"] = TextureName::CharacterHudChar09;
                m_strToTex["char10.png"] = TextureName::CharacterHudChar10;
                m_strToTex["char11.png"] = TextureName::CharacterHudChar11;
                m_strToTex["char12.png"] = TextureName::CharacterHudChar12;
                m_strToTex["char13.png"] = TextureName::CharacterHudChar13;
                m_strToTex["char14.png"] = TextureName::CharacterHudChar14;
                m_strToTex["char15.png"] = TextureName::CharacterHudChar15;
                m_strToTex["char16.png"] = TextureName::CharacterHudChar16;
                m_strToTex["char17.png"] = TextureName::CharacterHudChar17;
                m_strToTex["char18.png"] = TextureName::CharacterHudChar18;
                m_strToTex["char19.png"] = TextureName::CharacterHudChar19;
                m_strToTex["char20.png"] = TextureName::CharacterHudChar20;
                m_strToTex["char21.png"] = TextureName::CharacterHudChar21;
                m_strToTex["char22.png"] = TextureName::CharacterHudChar22;
                m_strToTex["char23.png"] = TextureName::CharacterHudChar23;
                m_strToTex["char24.png"] = TextureName::CharacterHudChar24;
                m_strToTex["char25.png"] = TextureName::CharacterHudChar25;
                m_strToTex["ghost1.png"] = TextureName::EnemyGhostFlyingGhost1;
                m_strToTex["ghost2.png"] = TextureName::EnemyGhostFlyingGhost2;
                m_strToTex["ghost3.png"] = TextureName::EnemyGhostFlyingGhost3;
                m_strToTex["ghost4.png"] = TextureName::EnemyGhostFlyingGhost4;
                m_strToTex["spider1.png"] = TextureName::EnemySpiderWalkSpider1;
                m_strToTex["spider2.png"] = TextureName::EnemySpiderWalkSpider2;
                m_strToTex["spider3.png"] = TextureName::EnemySpiderWalkSpider3;
                m_strToTex["spider4.png"] = TextureName::EnemySpiderWalkSpider4;
                m_strToTex["thing1.png"] = TextureName::EnemyThingWalkThing1;
                m_strToTex["thing2.png"] = TextureName::EnemyThingWalkThing2;
                m_strToTex["thing3.png"] = TextureName::EnemyThingWalkThing3;
                m_strToTex["thing4.png"] = TextureName::EnemyThingWalkThing4;
                m_strToTex["explosion-1.png"] = TextureName::Explosion1;
                m_strToTex["explosion-2.png"] = TextureName::Explosion2;
                m_strToTex["explosion-3.png"] = TextureName::Explosion3;
                m_strToTex["explosion-4.png"] = TextureName::Explosion4;
                m_strToTex["explosion-5.png"] = TextureName::Explosion5;
                m_strToTex["explosion-6.png"] = TextureName::Explosion6;
                m_strToTex["ui_big_pieces.png"] = TextureName::HudUiBigPieces;
                m_strToTex["swoosh.png"] = TextureName::MeleeSwoosh;
                m_strToTex["player-spritemap-greenpants.png"] = TextureName::PlayerSpritemapGreenpants;
                m_strToTex["player-spritemap-greypants.png"] = TextureName::PlayerSpritemapGreypants;
                m_strToTex["player-spritemap.png"] = TextureName::PlayerSpritemap;
                m_strToTex["player-spritemap-redpants.png"] = TextureName::PlayerSpritemapRedpants;
                m_strToTex["powerups-rpg-icons.png"] = TextureName::PowerupsRpgIcons;
                m_strToTex["fire1.png"] = TextureName::ShootFireFire1;
                m_strToTex["fire2.png"] = TextureName::ShootFireFire2;
                m_strToTex["jungle_terrain.png"] = TextureName::TilesJungleTerrain;
                m_strToTex["objects.png"] = TextureName::TilesObjects;

                m_texToRes[TextureName::Player] = ResourceName::GraphicsPlayer;
                m_texToRes[TextureName::Tileset1] = ResourceName::GraphicsTileset1;
                m_texToRes[TextureName::Tileset2] = ResourceName::GraphicsTileset2;
                m_texToRes[TextureName::BoulderSmall] = ResourceName::GraphicsBoulderSmall;
                m_texToRes[TextureName::Andre] = ResourceName::GraphicsAndre;
                m_texToRes[TextureName::PlayerSimple] = ResourceName::GraphicsPlayerSimple;
                m_texToRes[TextureName::MagicCliffsTileset] = ResourceName::GraphicsMagicCliffsTileset;
                m_texToRes[TextureName::Bat] = ResourceName::GraphicsEnemyBat;
                m_texToRes[TextureName::Crate] = ResourceName::GraphicsCrate;
                m_texToRes[TextureName::NinjaSmiley] = ResourceName::GraphicsNinjaSmiley;
                m_texToRes[TextureName::Jumpolini] = ResourceName::GraphicsJumpolini;
                m_texToRes[TextureName::Gem1] = ResourceName::GraphicsGem1;
                m_texToRes[TextureName::Gem2] = ResourceName::GraphicsGem2;
                m_texToRes[TextureName::Gem3] = ResourceName::GraphicsGem3;
                m_texToRes[TextureName::Gem4] = ResourceName::GraphicsGem4;

                m_texToRes[TextureName::Background01MountainsGrass] = ResourceName::GraphicsBackground01MountainsGrass;
                m_texToRes[TextureName::Background02MountainsDesert] = ResourceName::GraphicsBackground02MountainsDesert;
                m_texToRes[TextureName::Background03MountainsSnow] = ResourceName::GraphicsBackground03MountainsSnow;
                m_texToRes[TextureName::Background04CityNight] = ResourceName::GraphicsBackground04CityNight;
                m_texToRes[TextureName::Background05Graveyard] = ResourceName::GraphicsBackground05Graveyard;
                m_texToRes[TextureName::CharacterHudChar01] = ResourceName::GraphicsCharacterHudChar01;
                m_texToRes[TextureName::CharacterHudChar02] = ResourceName::GraphicsCharacterHudChar02;
                m_texToRes[TextureName::CharacterHudChar03] = ResourceName::GraphicsCharacterHudChar03;
                m_texToRes[TextureName::CharacterHudChar04] = ResourceName::GraphicsCharacterHudChar04;
                m_texToRes[TextureName::CharacterHudChar05] = ResourceName::GraphicsCharacterHudChar05;
                m_texToRes[TextureName::CharacterHudChar06] = ResourceName::GraphicsCharacterHudChar06;
                m_texToRes[TextureName::CharacterHudChar07] = ResourceName::GraphicsCharacterHudChar07;
                m_texToRes[TextureName::CharacterHudChar08] = ResourceName::GraphicsCharacterHudChar08;
                m_texToRes[TextureName::CharacterHudChar09] = ResourceName::GraphicsCharacterHudChar09;
                m_texToRes[TextureName::CharacterHudChar10] = ResourceName::GraphicsCharacterHudChar10;
                m_texToRes[TextureName::CharacterHudChar11] = ResourceName::GraphicsCharacterHudChar11;
                m_texToRes[TextureName::CharacterHudChar12] = ResourceName::GraphicsCharacterHudChar12;
                m_texToRes[TextureName::CharacterHudChar13] = ResourceName::GraphicsCharacterHudChar13;
                m_texToRes[TextureName::CharacterHudChar14] = ResourceName::GraphicsCharacterHudChar14;
                m_texToRes[TextureName::CharacterHudChar15] = ResourceName::GraphicsCharacterHudChar15;
                m_texToRes[TextureName::CharacterHudChar16] = ResourceName::GraphicsCharacterHudChar16;
                m_texToRes[TextureName::CharacterHudChar17] = ResourceName::GraphicsCharacterHudChar17;
                m_texToRes[TextureName::CharacterHudChar18] = ResourceName::GraphicsCharacterHudChar18;
                m_texToRes[TextureName::CharacterHudChar19] = ResourceName::GraphicsCharacterHudChar19;
                m_texToRes[TextureName::CharacterHudChar20] = ResourceName::GraphicsCharacterHudChar20;
                m_texToRes[TextureName::CharacterHudChar21] = ResourceName::GraphicsCharacterHudChar21;
                m_texToRes[TextureName::CharacterHudChar22] = ResourceName::GraphicsCharacterHudChar22;
                m_texToRes[TextureName::CharacterHudChar23] = ResourceName::GraphicsCharacterHudChar23;
                m_texToRes[TextureName::CharacterHudChar24] = ResourceName::GraphicsCharacterHudChar24;
                m_texToRes[TextureName::CharacterHudChar25] = ResourceName::GraphicsCharacterHudChar25;
                m_texToRes[TextureName::EnemyGhostFlyingGhost1] = ResourceName::GraphicsEnemyGhostFlyingGhost1;
                m_texToRes[TextureName::EnemyGhostFlyingGhost2] = ResourceName::GraphicsEnemyGhostFlyingGhost2;
                m_texToRes[TextureName::EnemyGhostFlyingGhost3] = ResourceName::GraphicsEnemyGhostFlyingGhost3;
                m_texToRes[TextureName::EnemyGhostFlyingGhost4] = ResourceName::GraphicsEnemyGhostFlyingGhost4;
                m_texToRes[TextureName::EnemySpiderWalkSpider1] = ResourceName::GraphicsEnemySpiderWalkSpider1;
                m_texToRes[TextureName::EnemySpiderWalkSpider2] = ResourceName::GraphicsEnemySpiderWalkSpider2;
                m_texToRes[TextureName::EnemySpiderWalkSpider3] = ResourceName::GraphicsEnemySpiderWalkSpider3;
                m_texToRes[TextureName::EnemySpiderWalkSpider4] = ResourceName::GraphicsEnemySpiderWalkSpider4;
                m_texToRes[TextureName::EnemyThingWalkThing1] = ResourceName::GraphicsEnemyThingWalkThing1;
                m_texToRes[TextureName::EnemyThingWalkThing2] = ResourceName::GraphicsEnemyThingWalkThing2;
                m_texToRes[TextureName::EnemyThingWalkThing3] = ResourceName::GraphicsEnemyThingWalkThing3;
                m_texToRes[TextureName::EnemyThingWalkThing4] = ResourceName::GraphicsEnemyThingWalkThing4;
                m_texToRes[TextureName::Explosion1] = ResourceName::GraphicsExplosion1;
                m_texToRes[TextureName::Explosion2] = ResourceName::GraphicsExplosion2;
                m_texToRes[TextureName::Explosion3] = ResourceName::GraphicsExplosion3;
                m_texToRes[TextureName::Explosion4] = ResourceName::GraphicsExplosion4;
                m_texToRes[TextureName::Explosion5] = ResourceName::GraphicsExplosion5;
                m_texToRes[TextureName::Explosion6] = ResourceName::GraphicsExplosion6;
                m_texToRes[TextureName::HudUiBigPieces] = ResourceName::GraphicsHudUiBigPieces;
                m_texToRes[TextureName::MeleeSwoosh] = ResourceName::GraphicsMeleeSwoosh;
                m_texToRes[TextureName::PlayerSpritemapGreenpants] = ResourceName::GraphicsPlayerSpritemapGreenpants;
                m_texToRes[TextureName::PlayerSpritemapGreypants] = ResourceName::GraphicsPlayerSpritemapGreypants;
                m_texToRes[TextureName::PlayerSpritemap] = ResourceName::GraphicsPlayerSpritemap;
                m_texToRes[TextureName::PlayerSpritemapRedpants] = ResourceName::GraphicsPlayerSpritemapRedpants;
                m_texToRes[TextureName::PowerupsRpgIcons] = ResourceName::GraphicsPowerupsRpgIcons;
                m_texToRes[TextureName::ShootFireFire1] = ResourceName::GraphicsShootFireFire1;
                m_texToRes[TextureName::ShootFireFire2] = ResourceName::GraphicsShootFireFire2;
                m_texToRes[TextureName::TilesJungleTerrain] = ResourceName::GraphicsTilesJungleTerrain;
                m_texToRes[TextureName::TilesObjects] = ResourceName::GraphicsTilesObjects;
            };

            TextureName getTextureNameByString(const std::string &id) override
            {
                return (m_strToTex.count(id) > 0) ? m_strToTex[id] : TextureName::None;
            }

            ResourceName getResourceNameByTextureName(TextureName id) override
            {
                return (m_texToRes.count(id) > 0) ? m_texToRes[id] : ResourceName::None;
            }

            AnimationName getAnimationNameByPlayerState(PlayerState playerState)
            {
                switch (playerState)
                {
                    case PlayerState::Idle:
                        return AnimationName::PlayerIdle;
                    case PlayerState::Walk:
                        return AnimationName::PlayerWalk;
                    case PlayerState::Jump:
                        return AnimationName::PlayerJump;
                    case PlayerState::Fall:
                        return AnimationName::PlayerFall;
                    default:
                        return AnimationName::None;
                }
            }

        private:
            std::map<TextureName, ResourceName> m_texToRes;
            std::map<std::string, TextureName> m_strToTex;
    };
}
#endif //GAME_DEV_TEMPLATE_MAPPER_HPP
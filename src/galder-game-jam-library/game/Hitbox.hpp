//
// Created by robin on 05.11.23.
//

#ifndef GALDER_GAME_JAM_2023_PROJECT_HITBOX_HPP
#define GALDER_GAME_JAM_2023_PROJECT_HITBOX_HPP

#include "raylib-cpp.hpp"
#include "box2d/box2d.h"
#include "../enums/PhysicsShape.h"
#include "../../gamedev-base/GameDevBase.h"
#include "../graphics/PhysicsObject.h"

namespace ggj
{
    
    class Hitbox : public PhysicsObject
    {
        public:
            Hitbox() = default;
            Hitbox(b2Body *body, const raylib::Vector2 &physicsSize, const raylib::Vector2 &spriteSize, const raylib::Rectangle &drawingRect, raylib::Texture * texture, const UserData &userData, bool isVisible = true)
            : PhysicsObject(body, physicsSize, (body->GetFixtureList()[0].GetShape()->GetType() == b2Shape::e_circle) ? PhysicsShape::Circle : PhysicsShape::Rectangle, userData, isVisible)
            {
            
            }
            
            void create(PhysicsObject *owner, b2World *world, const raylib::Vector2 &position, const raylib::Vector2 &size, raylib::Color color = raylib::Color::Red())
            {
                m_size = size;
                m_position = position;
                m_origin = raylib::Vector2(size.x / 2, size.y / 2);
                m_body = createBody(world, position, size);
                m_color = color;
                m_shape = ggj::PhysicsShape::Rectangle;
                m_isVisible = true;
            }
            
            void beginContact(PhysicsObject *a, PhysicsObject *b, b2Contact *contact) override
            {
                b2Body *body = contact->GetFixtureB()->GetBody();
                body->ApplyLinearImpulseToCenter({5.f, -5.f}, true);
            }
        
        protected:
            
            b2Body *createBody(b2World *world, const raylib::Vector2 &position, const raylib::Vector2 &size)
            {
                b2BodyType bodyType = b2_staticBody;
                
                b2BodyDef bodyDef;
                bodyDef.type = bodyType;
                
                b2Vec2 b2size = PhysicsObject::ConvertToB2Vec2({(float) size.x, (float) size.y});
                b2Vec2 b2origin = PhysicsObject::ConvertToB2Vec2({(float) size.x / 2, (float) size.y / 2});
                b2Vec2 b2pos = PhysicsObject::ConvertToB2Vec2({(float) position.x, (float) position.y});
                
                bodyDef.position.Set(b2pos.x + b2origin.x, b2pos.y + b2origin.y);
                b2Body *body = world->CreateBody(&bodyDef);
                
                //Create rectangle
                b2PolygonShape box;
                box.SetAsBox(b2size.x / 2 - b2_polygonRadius, b2size.y / 2 - b2_polygonRadius);
                b2FixtureDef fd;
                fd.shape = &box;
                fd.density = 1.0f; //Density must be something to react to gravity.
                fd.friction = 0.3f;
                body->CreateFixture(&fd);
                
                for (b2Fixture *f = body->GetFixtureList(); f; f = f->GetNext())
                {
                    f->SetSensor(true);
                }
                
                return body;
            }
            
        private:
            PhysicsObject *owner {nullptr};
    };
    
} // ggj

#endif //GALDER_GAME_JAM_2023_PROJECT_HITBOX_HPP

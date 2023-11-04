#include "Portal.h"

namespace ggj
{
    void Portal::beginContact(PhysicsObject *a, PhysicsObject *b, b2Contact *contact)
    {
        if(b->getUserData()->getObjectType() == ObjectType::Player)
        {
            teleport();
        }
    }

    void Portal::update(float timeDelta)
    {
        if(m_body == nullptr)
            return;

        m_body->SetLinearVelocity({m_velocity.x, m_velocity.y});

        PhysicsObject::update(timeDelta);

        if(m_animation.isValid())
        {
            m_animation.update(timeDelta);
            m_drawingRect = m_animation.getDrawingRect();
        }
    }

    void Portal::teleport()
    {
        //TODO: Implement teleport
    }
} // ggj
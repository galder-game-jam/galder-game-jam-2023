#include "Portal.h"

namespace ggj
{
    void Portal::beginContact(PhysicsObject *a, PhysicsObject *b, b2Contact *contact)
    {
        if(b->getUserData()->getObjectType() == ObjectType::Player)
        {
            if (!m_hasTeleported && m_activationTimer > m_activationTimeInSeconds)
            {
                m_hasTeleported = true;
                teleport();
            }
        }
    }

    void Portal::update(float timeDelta)
    {
        if(m_body == nullptr)
            return;

        if(m_activationTimer < m_activationTimeInSeconds)
        {
            m_activationTimer += timeDelta;
            if(m_activationTimer > m_activationTimeInSeconds)
                activate();
        }
        else if(m_hasTeleported && m_teleportTime > 0)
        {
            m_teleportTime -= timeDelta;
            if(m_teleportTime < 0)
            {
                close();
            }
        }

        m_body->SetLinearVelocity({m_velocity.x, m_velocity.y});

        PhysicsObject::update(timeDelta);

        if(m_animation.isValid())
        {
            m_animation.update(timeDelta);
            m_drawingRect = m_animation.getDrawingRect();
        }
    }

    void Portal::activate()
    {
        m_animation = m_animationManager.getAnimation(AnimationName::PortalActive);
    }

    void Portal::teleport()
    {
        m_animation = m_animationManager.getAnimation(AnimationName::PortalTeleport);
    }
    void Portal::close()
    {
        m_animation = m_animationManager.getAnimation(AnimationName::PortalIdle);
    }
} // ggj
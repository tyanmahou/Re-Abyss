#include "SlimeBaseState.hpp"
#include <abyss/controllers/Actors/Map/MapActor.hpp>

#include <abyss/utils/Collision/Collision.hpp>
#include <abyss/commons/ActInclude.hpp>
namespace abyss
{
    void SlimeBaseState::setup()
    {
        m_body = m_actor->getComponent<BodyModel>();
    }
    void SlimeBaseState::update(double dt)
    {
        if (m_body->isForward(Forward::Left)) {
            m_body->setAccelX(-720.0);
        }else if (m_body->isForward(Forward::Right)) {
            m_body->setAccelX(720.0f);
        }
        m_body->update(dt);
    }
    void SlimeBaseState::draw() const
    {}
    void SlimeBaseState::onCollisionStay(ICollider * col)
    {
        col->accept([this](const MapActor& map) {
            auto c = map.getCol();
            c.ignoredForVelocity(m_body->getVelocity());

            s3d::Vec2 before = m_body->region().center();
            auto [after, colDir] = collision::Collision(map.region(), m_body->region(), c);

            m_body->addPos(after - before);

            if (colDir.isUp()) {
                onColisionMapUp();
            }
            if (colDir.isRight()) {
                m_body->setForward(Forward::Right);
            }
            if (colDir.isLeft()) {
                m_body->setForward(Forward::Left);
            }
        });
    }
}

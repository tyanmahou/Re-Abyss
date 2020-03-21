#include "SlimeBaseState.hpp"
#include <abyss/commons/ActInclude.hpp>
namespace abyss
{
    void SlimeBaseState::setup()
    {
        m_body = &m_actor->getBody();
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

            auto colDir = m_body->fixPos(map.getMapColInfo());
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

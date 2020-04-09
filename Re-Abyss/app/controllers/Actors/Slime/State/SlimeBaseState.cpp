#include "SlimeBaseState.hpp"
#include <abyss/commons/ActInclude.hpp>
#include <abyss/params/Actors/Slime/SlimeParam.hpp>

namespace abyss
{
    void SlimeBaseState::setup()
    {
        m_body = this->binded<BodyModel>();
    }
    void SlimeBaseState::update(double dt)
    {
        if (m_body->isForward(Forward::Left)) {
            m_body->setAccelX(-SlimeParam::Walk::AccelX);
        }else if (m_body->isForward(Forward::Right)) {
            m_body->setAccelX(SlimeParam::Walk::AccelX);
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

        m_actor->EnemyActor::onCollisionStay(col);
    }
}

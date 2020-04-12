#include "SlimeBaseState.hpp"
#include <abyss/commons/ActInclude.hpp>
#include <abyss/controllers/ActionSystem/ActionSystem.hpp>
#include <abyss/params/Actors/Slime/SlimeParam.hpp>

namespace abyss
{
    void SlimeBaseState::setup()
    {
        m_body = this->binded<BodyModel>();
    }
    void SlimeBaseState::update(double dt)
    {
        m_body->setAccelX(m_body->getForward() * SlimeParam::Walk::AccelX);
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
    void SlimeBaseState::lastUpdate([[maybe_unused]]double dt)
    {
        if (auto colDir = m_body->fixPos(ActionSystem::Camera()->getCurrentRoom())) {
            if (colDir.isRight()) {
                m_body->setForward(Forward::Right);
            }
            if (colDir.isLeft()) {
                m_body->setForward(Forward::Left);
            }
        }
    }
}

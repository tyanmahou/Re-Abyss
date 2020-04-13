#include "RollingTakoBaseState.hpp"
#include <abyss/commons/ActInclude.hpp>
#include <abyss/controllers/ActionSystem/ActionSystem.hpp>
namespace abyss
{
    void RollingTakoBaseState::setup()
    {
        m_body = this->binded<BodyModel>();
    }
    void RollingTakoBaseState::update(double dt)
    {
        m_body->update(dt);
    }

    void RollingTakoBaseState::lastUpdate([[maybe_unused]] double dt)
    {
        if (auto colDir = m_body->fixPos(m_actor->getModule<Camera>()->getCurrentRoom())) {
            this->onCollisionMap(colDir);
        }
    }

    void RollingTakoBaseState::draw() const
    {

    }
    void RollingTakoBaseState::onCollisionMap(ColDirection colDir)
    {
        if (colDir.isRight()) {
            m_body->setVelocityX(0);
            m_body->setForward(Forward::Right);
        }
        if (colDir.isLeft()) {
            m_body->setVelocityX(0);
            m_body->setForward(Forward::Left);
        }
    }
    void RollingTakoBaseState::onCollisionStay(ICollider* col)
    {
        col->accept([this](const MapActor& map) {

            auto colDir = m_body->fixPos(map.getMapColInfo());

            if (colDir.isRight()) {
                m_body->setVelocityX(0);
                m_body->setForward(Forward::Right);
            }
            if (colDir.isLeft()) {
                m_body->setVelocityX(0);
                m_body->setForward(Forward::Left);
            }
        });

        m_actor->EnemyActor::onCollisionStay(col);
    }
}

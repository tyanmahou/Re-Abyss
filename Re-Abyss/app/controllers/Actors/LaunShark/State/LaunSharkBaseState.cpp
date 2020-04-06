#include "LaunSharkBaseState.hpp"
#include <abyss/commons/ActInclude.hpp>
#include <abyss/controllers/ActionSystem/ActionSystem.hpp>

namespace abyss
{

    void LaunSharkBaseState::setup()
    {
        m_body = this->binded<BodyModel>();
        m_timeCounter = this->binded<TimeCounterModel>();
    }

    void LaunSharkBaseState::tryReverse(ColDirection col)
    {
        if (col.isRight()) {
            m_body->setVelocityX(0);
            m_body->setForward(Forward::Right);
        }
        if (col.isLeft()) {
            m_body->setVelocityX(0);
            m_body->setForward(Forward::Left);
        }
    }

    void LaunSharkBaseState::onCollisionMap(ColDirection col)
    {
        this->tryReverse(col);
    }

    void LaunSharkBaseState::update(double dt)
    {
        m_timeCounter->update(dt);
        double accelX = LaunSharkParam::Base().accelX;
        if (m_body->isForward(Forward::Left)) {
            m_body->setAccelX(-accelX);
        } else if (m_body->isForward(Forward::Right)) {
            m_body->setAccelX(accelX);
        }
        m_body->update(dt);
    }
    void LaunSharkBaseState::lastUpdate([[maybe_unused]]double dt)
    {
        if (auto colDir = m_body->fixPos(ActionSystem::Camera()->getCurrentRoom())) {
            this->onCollisionMap(colDir);
        }
    }

    void LaunSharkBaseState::onCollisionStay(ICollider* col)
    {
        col->accept([this](const MapActor& map) {

            if (auto colDir = m_body->fixPos(map.getMapColInfo())) {
                this->onCollisionMap(colDir);
            }
        });

        m_actor->EnemyActor::onCollisionStay(col);
    }

}

#include "BaseState.hpp"
#include <abyss/commons/ActInclude.hpp>
#include <abyss/controllers/ActionSystem/ActionSystem.hpp>
#include <abyss/params/Actors/LaunShark/Param.hpp>

namespace abyss::LaunShark
{
    void BaseState::setup()
    {
        m_body = this->binded<BodyModel>();
        m_timeCounter = this->binded<TimeCounterModel>();
    }

    void BaseState::tryReverse(ColDirection col)
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

    void BaseState::onCollisionMap(ColDirection col)
    {
        this->tryReverse(col);
    }

    void BaseState::update(double dt)
    {
        m_timeCounter->update(dt);
        double accelX = Param::Base::AccelX;
        if (m_body->isForward(Forward::Left)) {
            m_body->setAccelX(-accelX);
        } else if (m_body->isForward(Forward::Right)) {
            m_body->setAccelX(accelX);
        }
        m_body->update(dt);
    }
    void BaseState::lastUpdate([[maybe_unused]]double dt)
    {
        if (auto colDir = m_body->fixPos(m_actor->getModule<Camera>()->getCurrentRoom(), true)) {
            this->onCollisionMap(colDir);
        }
    }

    void BaseState::onCollisionStay(ICollider* col)
    {
        col->accept([this](const MapActor& map) {

            if (auto colDir = m_body->fixPos(map.getMapColInfo())) {
                this->onCollisionMap(colDir);
            }
        });

        m_actor->EnemyActor::onCollisionStay(col);
    }

}

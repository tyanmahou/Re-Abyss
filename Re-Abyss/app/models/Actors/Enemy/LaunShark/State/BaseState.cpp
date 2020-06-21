#include "BaseState.hpp"
#include <abyss/controllers/System/System.hpp>
#include <abyss/models/Actors/Commons/MapColliderModel.hpp>
#include <abyss/params/Actors/Enemy/LaunShark/Param.hpp>

namespace abyss::LaunShark
{
    void BaseState::setup()
    {
        m_body = m_pActor->find<BodyModel>().get();
        m_mapCol = m_pActor->find<MapColliderModel>().get();
        m_timeCounter = m_pActor->find<TimeCounterModel>().get();
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
        if (m_mapCol->isHitForwardWall()) {
            m_body->setVelocityX(0);
            m_body->reversed();
        }
    }
}

#include "BaseState.hpp"
#include <abyss/modules/System/System.hpp>
#include <abyss/params/Actors/Enemy/LaunShark/Param.hpp>

namespace abyss::Actor::Enemy::LaunShark
{
    void BaseState::setup()
    {
        m_body = m_pActor->find<Body>().get();
        m_mapCol = m_pActor->find<MapCollider>().get();
        m_timeCounter = m_pActor->find<TimeCounter>().get();
        m_view = m_pActor->find<ViewCtrl<LaunSharkVM>>().get();
    }
    void BaseState::update()
    {
        auto dt = m_pActor->deltaTime();
        m_timeCounter->update(dt);
        double accelX = Param::Base::AccelX;
        if (m_body->isForward(Forward::Left)) {
            m_body->setAccelX(-accelX);
        } else if (m_body->isForward(Forward::Right)) {
            m_body->setAccelX(accelX);
        }
    }
    void BaseState::lastUpdate()
    {
        if (m_mapCol->isHitForwardWall()) {
            m_body->setVelocityX(0);
            m_body->reversed();
        }
    }
}

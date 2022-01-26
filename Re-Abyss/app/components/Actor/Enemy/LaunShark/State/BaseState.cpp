#include <abyss/components/Actor/Enemy/LaunShark/State/BaseState.hpp>
#include <abyss/params/Actor/Enemy/LaunShark/Param.hpp>

namespace abyss::Actor::Enemy::LaunShark
{
    void BaseState::onCache()
    {
        ComponentCache::onCache(m_pActor);
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

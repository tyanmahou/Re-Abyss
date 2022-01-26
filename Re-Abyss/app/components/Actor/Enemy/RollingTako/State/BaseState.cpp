#include <abyss/components/Actor/Enemy/RollingTako/State/BaseState.hpp>

namespace abyss::Actor::Enemy::RollingTako
{
    void BaseState::onCache()
    {
        ComponentCache::onCache(m_pActor);
    }

    void BaseState::lastUpdate()
    {
        if (m_mapCol->isHitForwardWall()) {
            m_body->setVelocityX(0);
            m_body->reversed();
        }
    }
}

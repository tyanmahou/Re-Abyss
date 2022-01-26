#include <abyss/components/Actor/Enemy/Schield/State/BaseState.hpp>

namespace abyss::Actor::Enemy::Schield
{
    void BaseState::onCache()
    {
        ComponentCache::onCache(m_pActor);
    }
}

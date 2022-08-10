#include <abyss/components/Actor/Enemy/BazookaKun/State/BaseState.hpp>

namespace abyss::Actor::Enemy::BazookaKun
{
    void BaseState::onCache()
    {
        ComponentCache::onCache(m_pActor);
    }
}

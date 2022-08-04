#include <abyss/components/Actor/Enemy/BabyDux/State/BaseState.hpp>

namespace abyss::Actor::Enemy::BabyDux
{
    void BaseState::onCache()
    {
        ComponentCache::onCache(m_pActor);
    }
}

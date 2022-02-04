#include <abyss/components/Actor/Enemy/KingDux/BabyDux/State/BaseState.hpp>

namespace abyss::Actor::Enemy::KingDux::BabyDux
{
    void BaseState::onCache()
    {
        ComponentCache::onCache(m_pActor);
    }
}

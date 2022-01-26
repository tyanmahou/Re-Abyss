#include <abyss/components/Actor/Enemy/KingDux/State/BaseState.hpp>

namespace abyss::Actor::Enemy::KingDux
{
    void BaseState::onCache()
    {
        ComponentCache::onCache(m_pActor);
    }
}

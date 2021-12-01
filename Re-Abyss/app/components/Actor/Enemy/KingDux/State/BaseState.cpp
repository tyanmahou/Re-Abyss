#include "BaseState.hpp"

namespace abyss::Actor::Enemy::KingDux
{
    void BaseState::onCache()
    {
        ComponentCache::onCache(m_pActor);
    }
}

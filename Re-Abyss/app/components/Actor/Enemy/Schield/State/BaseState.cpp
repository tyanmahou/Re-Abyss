#include "BaseState.hpp"

namespace abyss::Actor::Enemy::Schield
{
    void BaseState::onCache()
    {
        ComponentCache::onCache(m_pActor);
    }
}

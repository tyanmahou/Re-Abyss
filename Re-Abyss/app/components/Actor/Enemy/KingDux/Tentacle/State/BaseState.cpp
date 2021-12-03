#include "BaseState.hpp"

namespace abyss::Actor::Enemy::KingDux::Tentacle
{
    void BaseState::onCache()
    {
        ComponentCache::onCache(m_pActor);
    }
}

#include "BaseState.hpp"

namespace abyss::Actor::Enemy::Ikalien
{
    void BaseState::onCache()
    {
        ComponentCache::onCache(m_pActor);
    }
}

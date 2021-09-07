#include "BaseState.hpp"

namespace abyss::Actor::Enemy::LaunShark::Shot
{
    void BaseState::onCache()
    {
        ComponentCache::onCache(m_pActor);
    }
}

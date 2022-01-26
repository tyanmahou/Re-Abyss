#include <abyss/components/Actor/Enemy/KingDux/Tentacle/State/BaseState.hpp>

namespace abyss::Actor::Enemy::KingDux::Tentacle
{
    void BaseState::onCache()
    {
        ComponentCache::onCache(m_pActor);
    }
}

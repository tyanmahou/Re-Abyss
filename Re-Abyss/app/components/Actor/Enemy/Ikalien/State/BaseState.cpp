#include <abyss/components/Actor/Enemy/Ikalien/State/BaseState.hpp>

namespace abyss::Actor::Enemy::Ikalien
{
    void BaseState::onCache()
    {
        ComponentCache::onCache(m_pActor);
    }
}

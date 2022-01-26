#include <abyss/components/Actor/Enemy/CaptainTako/State/BaseState.hpp>

namespace abyss::Actor::Enemy::CaptainTako
{
    void BaseState::onCache()
    {
        ComponentCache::onCache(m_pActor);
    }
}

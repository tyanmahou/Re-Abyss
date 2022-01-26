#include <abyss/components/Actor/Enemy/CodeZero/Hand/State/BaseState.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    void BaseState::onCache()
    {
        ComponentCache::onCache(m_pActor);
    }
    void BaseState::update()
    {
    }
}

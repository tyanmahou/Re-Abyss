#include <abyss/components/Actor/Enemy/CodeZero/State/BaseState.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    BaseState::BaseState()
    {}
    void BaseState::onCache()
    {
        ComponentCache::onCache(m_pActor);
    }
    void BaseState::update()
    {
    }
}

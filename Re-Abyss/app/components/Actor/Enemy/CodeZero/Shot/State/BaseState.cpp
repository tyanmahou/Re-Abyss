#include <abyss/components/Actor/Enemy/CodeZero/Shot/State/BaseState.hpp>

namespace abyss::Actor::Enemy::CodeZero::Shot
{
    void BaseState::onCache()
    {
        ComponentCache::onCache(m_pActor);
    }
    void BaseState::lastUpdate()
    {
        if (m_parent->getHp()->isDead()) {
            m_pActor->destroy();
        }
    }
}

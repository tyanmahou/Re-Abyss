#include "BaseState.hpp"
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    BaseState::BaseState()
    {}
    void BaseState::onCache()
    {
        m_hp = m_pActor->find<HP>().get();
        m_behavior = m_pActor->find<BehaviorCtrl>().get();
        m_parts = m_pActor->find<PartsCtrl>().get();
    }
    void BaseState::update()
    {
    }
}

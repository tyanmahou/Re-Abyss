#include "BaseState.hpp"
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    BaseState::BaseState()
    {}
    void BaseState::setup()
    {
        m_hp = m_pActor->find<HP>().get();
        m_behavior = m_pActor->find<BehaviorCtrl>().get();
        m_parts = m_pActor->find<PartsCtrl>().get();
        m_view = m_pActor->find<ViewCtrl<Body::BodyVM>>().get();
    }
    void BaseState::update()
    {
    }
    void BaseState::draw() const
    {
        (*m_view)->draw();
    }
}

#include "BaseState.hpp"

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    void BaseState::setup()
    {
        m_parent = m_pActor->find<ParentCtrlModel>().get();
        m_body = m_pActor->find<BodyModel>().get();
        m_rotate = m_pActor->find<RotateModel>().get();
        m_hand = m_pActor->find<HandModel>().get();
        m_kind = m_pActor->find<KindModel>().get();

        m_view = m_pActor->find<ViewModel<HandVM>>().get();
    }
    void BaseState::update([[maybe_unused]]double dt)
    {
    }
    void BaseState::draw() const
    {
        (*m_view)->draw();
    }
}

#include "BaseState.hpp"

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    void BaseState::setup()
    {
        m_parent = m_pActor->find<ParentCtrl>().get();
        m_body = m_pActor->find<BodyModel>().get();
        m_rotate = m_pActor->find<RotateCtrl>().get();
        m_hand = m_pActor->find<HandCtrl>().get();
        m_kind = m_pActor->find<KindCtrl>().get();

        m_view = m_pActor->find<ViewCtrl<HandVM>>().get();
    }
    void BaseState::update([[maybe_unused]]double dt)
    {
    }
    void BaseState::draw() const
    {
        (*m_view)->draw();
    }
}

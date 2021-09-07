#include "BaseState.hpp"

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    void BaseState::onCache()
    {
        m_parent = m_pActor->find<ParentCtrl>().get();
        m_body = m_pActor->find<Body>().get();
        m_rotate = m_pActor->find<RotateCtrl>().get();
        m_hand = m_pActor->find<HandCtrl>().get();
        m_kind = m_pActor->find<KindCtrl>().get();

        m_view = m_pActor->find<ViewCtrl<HandVM>>().get();
    }
    void BaseState::update()
    {
    }
    void BaseState::draw() const
    {
        (*m_view)->draw();
    }
}

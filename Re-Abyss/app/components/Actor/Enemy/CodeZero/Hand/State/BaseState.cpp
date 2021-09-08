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
        m_motion = m_pActor->find<MotionCtrl>().get();
    }
    void BaseState::update()
    {
    }
}

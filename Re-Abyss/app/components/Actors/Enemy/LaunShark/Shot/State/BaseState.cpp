#include "BaseState.hpp"

namespace abyss::Actor::Enemy::LaunShark::Shot
{
    void BaseState::setup()
    {
        m_body = m_pActor->find<Body>().get();
        m_rotate = m_pActor->find<RotateCtrl>().get();

        m_view = m_pActor->find<ViewCtrl<ShotVM>>().get();
    }
}

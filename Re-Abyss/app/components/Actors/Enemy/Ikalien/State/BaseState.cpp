#include "BaseState.hpp"

namespace abyss::Actor::Enemy::Ikalien
{
    void BaseState::setup()
    {
        m_body = m_pActor->find<BodyModel>().get();
        m_rotate = m_pActor->find<RotateCtrl>().get();
        m_view = m_pActor->find<ViewCtrl<IkalienVM>>().get();
    }
}

#include "BaseState.hpp"

namespace abyss::Actor::Enemy::CaptainTako
{
    void BaseState::setup()
    {
        m_body = m_pActor->find<BodyModel>().get();
        m_view = m_pActor->find<ViewCtrl<CaptainTakoVM>>().get();
    }
}

#include "BaseState.hpp"

namespace abyss::Actor::Enemy::Schield
{
    void BaseState::setup()
    {
        m_face = m_pActor->find<FaceCtrl>().get();
        m_body = m_pActor->find<BodyModel>().get();
        m_view = m_pActor->find<ViewCtrl<SchieldVM>>().get();
    }
}

#include "BaseState.hpp"

namespace abyss::Actor::Schield
{
    void BaseState::setup()
    {
        m_face = m_pActor->find<FaceCtrlModel>().get();
        m_body = m_pActor->find<BodyModel>().get();
        m_view = m_pActor->find<ViewModel<SchieldVM>>().get();
    }
}

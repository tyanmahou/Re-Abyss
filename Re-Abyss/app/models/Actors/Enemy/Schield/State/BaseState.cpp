#include "BaseState.hpp"
#include <abyss/controllers/Actors/ActInclude.hpp>

namespace abyss::Schield
{
    void BaseState::setup()
    {
        m_face = m_pActor->find<FaceCtrlModel>().get();
        m_body = m_pActor->find<BodyModel>().get();
        m_draw = m_pActor->find<DrawModel>().get();
    }
}

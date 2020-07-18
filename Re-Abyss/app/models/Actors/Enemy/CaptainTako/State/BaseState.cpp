#include "BaseState.hpp"

namespace abyss::CaptainTako
{
    void BaseState::setup()
    {
        m_body = m_pActor->find<BodyModel>().get();
        m_draw = m_pActor->find<DrawModel>().get();
    }
}

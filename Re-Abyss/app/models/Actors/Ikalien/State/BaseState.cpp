#include "BaseState.hpp"

namespace abyss::Ikalien
{
    void BaseState::setup()
    {
        m_body = m_pActor->findComponent<BodyModel>().get();
        m_rotate = m_pActor->findComponent<RotateModel>().get();
    }
}

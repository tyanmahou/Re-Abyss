#include "BaseState.hpp"

namespace abyss::Ikalien
{
    void BaseState::setup()
    {
        m_body = m_pActor->find<BodyModel>().get();
        m_rotate = m_pActor->find<RotateModel>().get();
        m_view = m_pActor->find<ViewModel<IkalienVM>>().get();
    }
}

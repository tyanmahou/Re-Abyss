#include "BaseState.hpp"

namespace abyss::LaunShark::Shot
{
    void BaseState::setup()
    {
        m_body = m_pActor->find<BodyModel>().get();
        m_rotate = m_pActor->find<RotateModel>().get();

        m_draw = m_pActor->find<DrawModel>().get();
    }
}

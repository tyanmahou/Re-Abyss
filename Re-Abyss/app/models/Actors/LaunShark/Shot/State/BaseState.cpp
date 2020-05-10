#include "BaseState.hpp"
#include <abyss/commons/ActInclude.hpp>
#include <abyss/controllers/World/World.hpp>

namespace abyss::LaunShark::Shot
{
    void BaseState::setup()
    {
        m_body = m_pActor->findComponent<BodyModel>().get();
        m_rotate = m_pActor->findComponent<RotateModel>().get();
    }
}

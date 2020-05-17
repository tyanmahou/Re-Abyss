#include "BaseState.hpp"
#include <abyss/controllers/Actors/ActInclude.hpp>
#include <abyss/controllers/World/World.hpp>

namespace abyss::LaunShark::Shot
{
    void BaseState::setup()
    {
        m_body = m_pActor->find<BodyModel>().get();
        m_rotate = m_pActor->find<RotateModel>().get();
    }
}

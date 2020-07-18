#include "BaseState.hpp"
#include <abyss/models/Actors/Commons/HPModel.hpp>

namespace abyss::CodeZero::Shot
{
    void BaseState::setup()
    {
        m_parent = m_pActor->find<ParentCtrlModel>().get();
        m_body = m_pActor->find<BodyModel>().get();
        m_scale = m_pActor->find<ScaleModel>().get();
        m_draw = m_pActor->find<DrawModel>().get();
    }
    void BaseState::lastUpdate()
    {
        if (m_parent->getHp()->isDead()) {
            m_pActor->destroy();
        }
    }
}

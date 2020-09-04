#include "BaseState.hpp"
#include <abyss/models/Actors/Commons/HPModel.hpp>

namespace abyss::Actor::CodeZero::Shot
{
    void BaseState::setup()
    {
        m_parent = m_pActor->find<ParentCtrlModel>().get();
        m_body = m_pActor->find<BodyModel>().get();
        m_scale = m_pActor->find<ScaleModel>().get();
        m_view = m_pActor->find<ViewModel<ShotVM>>().get();
    }
    void BaseState::lastUpdate()
    {
        if (m_parent->getHp()->isDead()) {
            m_pActor->destroy();
        }
    }

    void BaseState::draw() const
    {
        (*m_view)->draw();
    }
}

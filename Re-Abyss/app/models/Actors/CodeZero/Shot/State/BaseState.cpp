#include "BaseState.hpp"
#include <abyss/views/Actors/CodeZero/Shot/ShotVM.hpp>
#include <abyss/models/Actors/Commons/HPModel.hpp>

namespace abyss::CodeZero::Shot
{
    void BaseState::setup()
    {
        m_parent = m_pActor->findComponent<ParentCtrlModel>().get();
        m_body = m_pActor->findComponent<BodyModel>().get();
        m_scale = m_pActor->findComponent<ScaleModel>().get();
    }
    void BaseState::lastUpdate([[maybe_unused]]double dt)
    {
        if (m_parent->getHp()->isDead()) {
            m_pActor->destroy();
        }
    }
    void BaseState::draw() const
    {
        m_pActor->getBindedView()->draw();
    }
}

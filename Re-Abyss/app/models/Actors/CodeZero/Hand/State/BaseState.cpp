#include "BaseState.hpp"
#include <abyss/views/Actors/CodeZero/Hand/HandVM.hpp>

namespace abyss::CodeZero::Hand
{
    void BaseState::update([[maybe_unused]]double dt)
    {
    }
    void BaseState::setup()
    {
        m_parent = m_pActor->findComponent<ParentCtrlModel>()->getParent();
        m_body = m_pActor->findComponent<BodyModel>().get();
        m_rotate = m_pActor->findComponent<RotateModel>().get();
        m_hand = m_pActor->findComponent<HandModel>().get();
    }
    void BaseState::draw() const
    {
        m_pActor->getBindedView()->draw();
    }
}

#include "BaseState.hpp"
#include <abyss/views/Actors/Enemy/CodeZero/Hand/HandVM.hpp>

namespace abyss::CodeZero::Hand
{
    void BaseState::update([[maybe_unused]]double dt)
    {
    }
    void BaseState::setup()
    {
        m_parent = m_pActor->find<ParentCtrlModel>()->getParent();
        m_body = m_pActor->find<BodyModel>().get();
        m_rotate = m_pActor->find<RotateModel>().get();
        m_hand = m_pActor->find<HandModel>().get();
    }
    void BaseState::draw() const
    {
        m_pActor->getBindedView()->draw();
    }
}

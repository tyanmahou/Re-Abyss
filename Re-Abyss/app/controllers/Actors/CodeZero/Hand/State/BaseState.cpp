#include "BaseState.hpp"
#include <abyss/views/Actors/CodeZero/Hand/HandVM.hpp>

namespace abyss::CodeZero::Hand
{
    void BaseState::update([[maybe_unused]]double dt)
    {
    }
    void BaseState::setup()
    {
        m_parent = *this->binded<CodeZeroActor*>();
        m_body = this->binded<BodyModel>();
        m_rotate = this->binded<RotateModel>();
        m_hand = this->binded<CodeZeroHandModel>();
    }
    void BaseState::draw() const
    {
        m_actor->getBindedView()->draw();
    }
}

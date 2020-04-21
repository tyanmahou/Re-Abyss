#include "CodeZeroHandBaseState.hpp"
#include <abyss/views/Actors/CodeZero/Hand/CodeZeroHandVM.hpp>

namespace abyss
{
    void CodeZeroHandBaseState::update([[maybe_unused]]double dt)
    {
    }
    void CodeZeroHandBaseState::setup()
    {
        m_parent = *this->binded<CodeZeroActor*>();
        m_body = this->binded<BodyModel>();
        m_rotate = this->binded<RotateModel>();
        m_hand = this->binded<CodeZeroHandModel>();
    }
    void CodeZeroHandBaseState::draw() const
    {
        m_actor->getBindedView()->draw();
    }
}

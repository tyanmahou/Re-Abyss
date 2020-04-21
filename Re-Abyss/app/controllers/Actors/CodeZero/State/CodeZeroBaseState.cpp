#include "CodeZeroBaseState.hpp"
#include <abyss/views/Actors/CodeZero/Body/CodeZeroBodyVM.hpp>

#include <Siv3D.hpp>

namespace abyss
{
    CodeZeroBaseState::CodeZeroBaseState()
    {}
    void CodeZeroBaseState::setup()
    {
        m_hp = this->binded<HPModel>();
    }
    void CodeZeroBaseState::update([[maybe_unused]]double dt)
    {
    }
    void CodeZeroBaseState::draw() const
    {
        m_actor->getBindedView()->draw();
    }
}

#include "CodeZeroBaseState.hpp"
#include <abyss/views/Actors/CodeZero/Body/CodeZeroBodyVM.hpp>
namespace abyss
{
    void CodeZeroBaseState::setup()
    {}
    void CodeZeroBaseState::update([[maybe_unused]]double dt)
    {
    
    }
    void CodeZeroBaseState::draw() const
    {
        m_actor->getBindedView()->draw();
    }
}

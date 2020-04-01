#include "LaunSharkSwimState.hpp"
#include <abyss/views/Actors/LaunShark/LaunSharkVM.hpp>

namespace abyss
{
    void LaunSharkSwimState::update(double dt)
    {
        m_totalTime += dt;
    }
    void LaunSharkSwimState::draw() const
    {
        m_actor->getBindedView()->drawSwim();
    }
}

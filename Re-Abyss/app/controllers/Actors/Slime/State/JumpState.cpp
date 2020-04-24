#include "JumpState.hpp"

#include <abyss/views/Actors/Slime/SlimeVM.hpp>
#include <abyss/params/Actors/Slime/Param.hpp>
namespace abyss::Slime
{
    void JumpState::onColisionMapUp()
    {
        this->changeState(State::Walk);
    }
    void JumpState::start()
    {
        m_body->setSize(Param::Jump::Size).setPivot({ 0, 0 });

        m_body->jumpToHeight(Param::Jump::JumpHeight);
    }
    void JumpState::draw() const
    {
        m_actor->getBindedView()->drawJump();
    }
}

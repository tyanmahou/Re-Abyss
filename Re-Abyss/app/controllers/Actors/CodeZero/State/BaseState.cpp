#include "BaseState.hpp"
#include <abyss/views/Actors/CodeZero/Body/BodyVM.hpp>

#include <Siv3D.hpp>

namespace abyss::CodeZero
{
    BaseState::BaseState()
    {}
    void BaseState::setup()
    {
        m_hp = this->binded<HPModel>();
    }
    void BaseState::update([[maybe_unused]]double dt)
    {
    }
    void BaseState::draw() const
    {
        m_actor->getBindedView()->draw();
    }
}

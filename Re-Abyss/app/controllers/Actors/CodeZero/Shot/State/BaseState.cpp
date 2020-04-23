#include "BaseState.hpp"
#include <abyss/views/Actors/CodeZero/Shot/ShotVM.hpp>

namespace abyss::CodeZero::Shot
{
    void BaseState::setup()
    {
        m_body = this->binded<BodyModel>();
        m_scale = this->binded<ScaleModel>();
    }
    void BaseState::draw() const
    {
        m_actor->getBindedView()->draw();
    }
}

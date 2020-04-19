#include "CodeZeroHandBaseState.hpp"
#include <abyss/views/Actors/CodeZero/Hand/CodeZeroHandVM.hpp>

namespace abyss
{
    void CodeZeroHandBaseState::update(double dt)
    {
        if (m_actor->getKind() == CodeZeroHandActor::Kind::Left) {
            this->updateLeft(dt);
        } else {
            this->updateRight(dt);
        }
    }
    void CodeZeroHandBaseState::setup()
    {
        m_parent = *this->binded<CodeZeroActor*>();
        m_body = this->binded<BodyModel>();
        m_rotate = this->binded<RotateModel>();
    }
    void CodeZeroHandBaseState::draw() const
    {
        m_actor->getBindedView()->draw();
    }
}

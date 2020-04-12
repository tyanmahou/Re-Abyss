#include "SchieldBaseState.hpp"
#include <abyss/commons/ActInclude.hpp>

namespace abyss
{
    void SchieldBaseState::setup()
    {
        m_body = this->binded<BodyModel>();
    }
    void SchieldBaseState::update(double dt)
    {
        m_body->update(dt);
    }
    void SchieldBaseState::onCollisionStay(ICollider* col)
    {
        col->accept([this](const MapActor& map) {
            m_body->fixPos(map.getMapColInfo());
        });
    }
}

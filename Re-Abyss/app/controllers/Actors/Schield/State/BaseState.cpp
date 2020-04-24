#include "BaseState.hpp"
#include <abyss/commons/ActInclude.hpp>

namespace abyss::Schield
{
    void BaseState::setup()
    {
        m_body = this->binded<BodyModel>();
    }
    void BaseState::update(double dt)
    {
        m_body->update(dt);
    }
    void BaseState::onCollisionStay(ICollider* col)
    {
        col->accept([this](const MapActor& map) {
            m_body->fixPos(map.getMapColInfo());
        });
    }
}

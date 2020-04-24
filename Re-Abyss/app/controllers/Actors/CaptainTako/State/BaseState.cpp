#include "BaseState.hpp"
#include <abyss/commons/ActInclude.hpp>

namespace abyss::CaptainTako
{
    void BaseState::setup()
    {
        m_body = this->binded<BodyModel>();
    }
    void BaseState::update(double dt)
    {
        m_body->update(dt);
    }
    void BaseState::draw() const
    {}
    void BaseState::onCollisionStay(ICollider * col)
    {
        col->accept([this](const MapActor& map) {
            auto colDir = m_body->fixPos(map.getMapColInfo());
        });

        m_actor->EnemyActor::onCollisionStay(col);
    }
}

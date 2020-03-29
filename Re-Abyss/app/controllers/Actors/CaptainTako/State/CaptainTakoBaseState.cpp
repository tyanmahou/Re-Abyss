#include "CaptainTakoBaseState.hpp"
#include <abyss/commons/ActInclude.hpp>

namespace abyss
{
    void CaptainTakoBaseState::setup()
    {
        m_body = this->binded<BodyModel>();
    }
    void CaptainTakoBaseState::update(double dt)
    {
        m_body->update(dt);
    }
    void CaptainTakoBaseState::draw() const
    {}
    void CaptainTakoBaseState::onCollisionStay(ICollider * col)
    {
        col->accept([this](const MapActor& map) {
            auto colDir = m_body->fixPos(map.getMapColInfo());
        });

        m_actor->EnemyActor::onCollisionStay(col);
    }
}

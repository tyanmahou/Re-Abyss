#include "BaseState.hpp"
#include <abyss/commons/ActInclude.hpp>

namespace abyss::CaptainTako
{
    void BaseState::setup()
    {
        m_body = m_pActor->find<BodyModel>().get();
    }
    void BaseState::update(double dt)
    {
        m_body->update(dt);
    }
    void BaseState::draw() const
    {}
    void BaseState::onCollisionStay(IActor * col)
    {
        col->accept([this](const MapActor& map) {
            m_body->fixPos(map.getMapColInfo());
        });
    }
}

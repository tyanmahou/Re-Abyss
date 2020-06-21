#include "BaseState.hpp"
#include <abyss/controllers/Actors/ActInclude.hpp>
#include <abyss/controllers/System/System.hpp>
#include <abyss/params/Actors/Enemy/Slime/Param.hpp>

namespace abyss::Slime
{
    void BaseState::setup()
    {
        m_body = this->m_pActor->find<BodyModel>().get();
        m_mapColResult = this->m_pActor->find<MapColResultModel>().get();
    }
    void BaseState::update(double dt)
    {
        m_body->setAccelX(m_body->getForward() * Param::Walk::AccelX);
        m_body->update(dt);
    }
    void BaseState::draw() const
    {}

    void BaseState::lastUpdate([[maybe_unused]]double dt)
    {
        if (m_mapColResult->isHitWall(m_body->getForward())) {
            m_body->reversed();
        }
    }
}

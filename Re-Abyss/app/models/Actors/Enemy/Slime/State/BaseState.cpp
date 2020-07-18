#include "BaseState.hpp"
#include <abyss/controllers/System/System.hpp>
#include <abyss/params/Actors/Enemy/Slime/Param.hpp>

namespace abyss::Slime
{
    void BaseState::setup()
    {
        m_body = this->m_pActor->find<BodyModel>().get();
        m_mapCol = this->m_pActor->find<MapColliderModel>().get();
        m_draw = m_pActor->find<DrawModel>().get();
    }
    void BaseState::update([[maybe_unused]]double dt)
    {
        m_body->setAccelX(m_body->getForward() * Param::Walk::AccelX);
    }

    void BaseState::lastUpdate()
    {
        if (m_mapCol->isHitForwardWall()) {
            m_body->reversed();
        }
    }
}

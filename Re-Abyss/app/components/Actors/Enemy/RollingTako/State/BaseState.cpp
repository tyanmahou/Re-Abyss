#include "BaseState.hpp"
#include <abyss/controllers/System/System.hpp>
#include <abyss/components/Actors/Commons/MapCollider.hpp>

namespace abyss::Actor::Enemy::RollingTako
{
    void BaseState::setup()
    {
        m_body = this->m_pActor->find<Body>().get();
        m_mapCol = this->m_pActor->find<MapCollider>().get();
        m_view = this->m_pActor->find<ViewCtrl<RollingTakoVM>>().get();
    }

    void BaseState::lastUpdate()
    {
        if (m_mapCol->isHitForwardWall()) {
            m_body->setVelocityX(0);
            m_body->reversed();
        }
    }
}

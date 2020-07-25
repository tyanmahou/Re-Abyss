#include "BaseState.hpp"
#include <abyss/controllers/System/System.hpp>
#include <abyss/models/Actors/Commons/MapColliderModel.hpp>

namespace abyss::RollingTako
{
    void BaseState::setup()
    {
        m_body = this->m_pActor->find<BodyModel>().get();
        m_mapCol = this->m_pActor->find<MapColliderModel>().get();
        m_view = this->m_pActor->find<ViewModel<RollingTakoVM>>().get();
    }

    void BaseState::lastUpdate()
    {
        if (m_mapCol->isHitForwardWall()) {
            m_body->setVelocityX(0);
            m_body->reversed();
        }
    }
}

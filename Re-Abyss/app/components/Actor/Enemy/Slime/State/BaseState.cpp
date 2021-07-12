#include "BaseState.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/params/Actor/Enemy/Slime/Param.hpp>

namespace abyss::Actor::Enemy::Slime
{
    void BaseState::setup()
    {
        m_body = this->m_pActor->find<Body>().get();
        m_mapCol = this->m_pActor->find<MapCollider>().get();
        m_view = m_pActor->find<ViewCtrl<SlimeVM>>().get();
    }
    void BaseState::update()
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

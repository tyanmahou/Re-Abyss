#include "BaseState.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/params/Actor/Enemy/Slime/Param.hpp>

namespace abyss::Actor::Enemy::Slime
{
    void BaseState::onCache()
    {
        ComponentCache::onCache(m_pActor);
    }
    void BaseState::updateMove()
    {
        m_body->setAccelX(m_body->getForward() * Param::Walk::AccelX);
    }

    void BaseState::checkWallHit()
    {
        if (m_mapCol->isHitForwardWall()) {
            m_body->reversed();
        }
    }
}

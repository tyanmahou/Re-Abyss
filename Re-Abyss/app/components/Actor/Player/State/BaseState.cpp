#include "BaseState.hpp"

#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/views/Actor/Player/PlayerVM.hpp>
#include <abyss/params/Actor/Player/Param.hpp>
#include <abyss/components/Actor/Common/ICollider.hpp>

namespace abyss::Actor::Player
{
    void BaseState::onCache()
    {
        ComponentCache::onCache(m_pActor);
    }
    void BaseState::start()
    {
        (*m_body)
            .setAccelX(0)
            .setAccelY(Body::DefaultGravity)
            .setVelocity({0, 0})
            .setMaxVelocityY(Body::DefaultMaxVelocityY)
            .setDecelX(Param::Swim::DecelX)
            .setMaxSpeedX(Param::Swim::MaxSpeedX);
    }
    void BaseState::update()
    {
    }

    void BaseState::lastUpdate()
    {
        if (m_mapCol->isHitGround()) {
            if (m_body->getVelocity().y > 0) {
                m_body->setVelocityY(0);
            }
            this->onLanding();
        }
    }
}

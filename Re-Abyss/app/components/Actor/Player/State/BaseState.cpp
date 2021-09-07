#include "BaseState.hpp"

#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/views/Actor/Player/PlayerVM.hpp>
#include <abyss/params/Actor/Player/Param.hpp>
#include <abyss/components/Actor/base/ICollider.hpp>

namespace abyss::Actor::Player
{
    void BaseState::onCache()
    {
        m_body       = m_pActor->find<Body>().get();
        m_foot       = m_pActor->find<Foot>().get();
        m_attackCtrl = m_pActor->find<AttackCtrl>().get();
        m_mapCol     = m_pActor->find<MapCollider>().get();
        m_view       = m_pActor->find<ViewCtrl<PlayerVM>>().get();
        m_colCtrl    = m_pActor->find<CollisionCtrl>().get();
        m_stateChecker = m_pActor->find<StateChecker>().get();
        m_damageCtrl = m_pActor->find<DamageCtrl>().get();
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
    void BaseState::draw() const
    {
        auto view = m_view->getBindedView();
        if (!view) {
            return;
        }

        this->onDraw(*view);

        view->drawCharge();
    }
}

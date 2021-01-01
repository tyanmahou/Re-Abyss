#include "BaseState.hpp"

#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/views/Actors/Player/PlayerVM.hpp>
#include <abyss/params/Actors/Player/Param.hpp>
#include <abyss/components/Actors/base/ICollider.hpp>

namespace abyss::Actor::Player
{
    bool BaseState::onCollisionStay([[maybe_unused]]const PenetrateFloorProxy& col)
    {
        return false;
    }
    bool BaseState::onCollisionStay(const LadderProxy& ladder)
    {
        if (ladder.isTop()) {
            return this->onCollisionStayLadderTop(ladder);
        }
        return false;
    }
    bool BaseState::onCollisionStayLadderTop([[maybe_unused]] const LadderProxy& ladder)
    {
        return false;
    }
    void BaseState::setup()
    {
        m_body       = m_pActor->find<Body>().get();
        m_foot       = m_pActor->find<Foot>().get();
        m_hp         = m_pActor->find<HP>().get();
        m_attackCtrl = m_pActor->find<AttackCtrl>().get();
        m_mapCol     = m_pActor->find<MapCollider>().get();
        m_view       = m_pActor->find<ViewCtrl<PlayerVM>>().get();
        m_colCtrl    = m_pActor->find<CollisionCtrl>().get();
        m_stateChecker = m_pActor->find<StateChecker>().get();
    }
    Task<> BaseState::start()
    {
        (*m_body)
            .setAccelY(Body::DefaultGravity)
            .setVelocity({0, 0})
            .setMaxVelocityY(Body::DefaultMaxVelocityY)
            .setDecelX(Param::Swim::DecelX)
            .setMaxSpeedX(Param::Swim::MaxSpeedX);
        co_return;
    }
    void BaseState::onMove([[maybe_unused]] double dt)
    {
        const bool rightPressed = InputManager::Right.pressed();
        const bool leftPressed = InputManager::Left.pressed();

        m_body->setAccelX(Param::Swim::AccelX *(rightPressed - leftPressed));
        // ジャンプ
        if (InputManager::Jump.down()) {
            m_body->jumpToHeight(Param::Swim::JumpHeight);
            m_pActor->find<AudioSource>()->play(U"Swim");
        }
        if (InputManager::Down.pressed()) {
            m_body->setMaxVelocityY(Param::Swim::DiveSpeed);
        } else {
            m_body->setMaxVelocityY(Body::DefaultMaxVelocityY);
        }
    }
    void BaseState::update()
    {
        const bool rightPressed = InputManager::Right.pressed();
        const bool leftPressed = InputManager::Left.pressed();
        if (rightPressed) {
            m_body->setForward(Forward::Right);
        } else if (leftPressed) {
            m_body->setForward(Forward::Left);
        }
        // 地形判定
        for (auto* other : m_mapCol->getHitActors()) {
            if (other->getTag().is<Tag::Ladder>()) {
                // 梯子
                if (auto ladder = other->find<LadderProxy>()) {
                    if (this->onCollisionStay(*ladder)) {
                        break;
                    }
                }
            } else if (other->getTag().is<Tag::PenetrateFloor>()) {
                // 貫通床
                if (auto ladder = other->find<PenetrateFloorProxy>()) {
                    if (this->onCollisionStay(*ladder)) {
                        break;
                    }
                }
            }
        }
        this->onMove(m_pActor->deltaTime());
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

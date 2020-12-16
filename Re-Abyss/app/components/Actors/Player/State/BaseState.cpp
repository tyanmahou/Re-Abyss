#include "BaseState.hpp"
#include "DamageState.hpp"

#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/views/Actors/Player/PlayerVM.hpp>
#include <abyss/components/Actors/Commons/AttackerData.hpp>
#include <abyss/controllers/World/World.hpp>
#include <abyss/controllers/Actors/Player/Shot/ShotActor.hpp>
#include <abyss/params/Actors/Player/Param.hpp>
#include <abyss/components/Actors/Player/AttackCtrl.hpp>
#include <abyss/components/Actors/base/ICollider.hpp>

#include <abyss/controllers/Actors/Map/Ladder/LadderActor.hpp>

namespace abyss::Actor::Player
{
    void BaseState::onCollisionStay([[maybe_unused]]const PenetrateFloorProxy& col)
    {
    }
    void BaseState::onCollisionStay(const LadderProxy& ladder)
    {
        if (ladder.isTop()) {
            this->onCollisionStayLadderTop(ladder);
        }
    }
    void BaseState::onCollisionStayLadderTop([[maybe_unused]] const LadderProxy& ladder)
    {
    }
    void BaseState::onCollisionStay([[maybe_unused]]const DoorActor & col)
    {}
    void BaseState::setup()
    {
        m_body       = m_pActor->find<Body>().get();
        m_foot       = m_pActor->find<Foot>().get();
        m_charge     = m_pActor->find<ChargeCtrl>().get();
        m_hp         = m_pActor->find<HP>().get();
        m_attackCtrl = m_pActor->find<AttackCtrl>().get();
        m_mapCol     = m_pActor->find<MapCollider>().get();
        m_view       = m_pActor->find<ViewCtrl<PlayerVM>>().get();
    }
    void BaseState::start()
    {
        (*m_body)
            .setAccelY(Body::DefaultGravity)
            .setVelocity({0, 0})
            .setMaxVelocityY(Body::DefaultMaxVelocityY)
            .setDecelX(Param::Swim::DecelX)
            .setMaxSpeedX(Param::Swim::MaxSpeedX);
    }
    void BaseState::onMove(double dt)
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
        m_body->update(dt);
    }
    void BaseState::update()
    {
        auto dt = m_pActor->deltaTime();

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
                    this->onCollisionStay(*ladder);
                }
            } else if (other->getTag().is<Tag::PenetrateFloor>()) {
                // 貫通床
                if (auto ladder = other->find<PenetrateFloorProxy>()) {
                    this->onCollisionStay(*ladder);
                }
            }
        }
        this->onMove(m_pActor->deltaTime());

        // 攻撃
        if (m_charge->update(dt)) {
            double charge = m_charge->pop();
            m_pActor->getModule<World>()->create<Shot::ShotActor>(m_body->getPos() + Vec2{30 * m_body->getForward(), -1}, m_body->getForward(), charge);
            m_attackCtrl->startAttack();
        }
    }
    void BaseState::onCollisionStay(ICollider * col)
    {
        // FIXME
        //col->getActor()->accept(overloaded{
        //    [this](const DoorActor& door) {
        //        // 扉
        //        this->onCollisionStay(door);
        //    },
        //});

        col->isThen<Tag::Attacker, AttackerData>([this](const AttackerData& attacker) {
            if (m_hp->damage(attacker.getPower())) {
                this->changeState<DamageState>();
            }
        });
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

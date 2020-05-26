#include "BaseState.hpp"
#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/views/Actors/Player/PlayerVM.hpp>
#include <abyss/controllers/Actors/ActInclude.hpp>
#include <abyss/controllers/World/World.hpp>
#include <abyss/controllers/Actors/Player/Shot/ShotActor.hpp>
#include <abyss/params/Actors/Player/Param.hpp>
#include <abyss/models/Actors/Player/AttackCtrlModel.hpp>

namespace abyss::Player
{
    ColDirection BaseState::fixPos(const MapColInfo& mapColInfo)
    {
        auto col = m_body->fixPos(mapColInfo);
        if (col.isUp()) {
            if (m_body->getVelocity().y > 0) {
                m_body->setVelocityY(0);
            }
            *m_foot |= FootModel::Landing;
            this->onLanding();
        }
        return col;
    }
    void BaseState::onCollisionStay(const FloorActor& col)
    {
        this->fixPos(col.getMapColInfo());
    }
    void BaseState::onCollisionStay(const PenetrateFloorActor& col)
    {
        this->fixPos(col.getMapColInfo());
    }
    void BaseState::onCollisionStay(const LadderActor & ladder)
    {
        if (ladder.isTop()) {
            this->onCollisionStayLadderTop(ladder);
        }
        if (ladder.getCenterLine().intersects(m_body->region())) {
            m_foot->setLadderPosX(ladder.getPos().x);
            auto state = ladder.isTop() ? FootModel::LadderTop : FootModel::Ladder;
            (*m_foot) |= state;
        }
    }
    void BaseState::onCollisionStayLadderTop(const LadderActor& ladder)
    {
        this->fixPos(ladder.getMapColInfo());
    }
    void BaseState::onCollisionStay([[maybe_unused]]const DoorActor & col)
    {}
    void BaseState::setup()
    {
        m_body   = m_pActor->find<BodyModel>().get();
        m_foot   = m_pActor->find<FootModel>().get();
        m_charge = m_pActor->find<ChargeModel>().get();
        m_hp     = m_pActor->find<HPModel>().get();
    }
    void BaseState::start()
    {
        (*m_body)
            .setAccelY(BodyModel::DefaultGravity)
            .setVelocity({0, 0})
            .setMaxVelocityY(BodyModel::DefaultMaxVelocityY)
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
            m_pActor->find<AudioSourceModel>()->play(U"Player/swim.ogg");
        }
        if (InputManager::Down.pressed()) {
            m_body->setMaxVelocityY(Param::Swim::DiveSpeed);
        } else {
            m_body->setMaxVelocityY(BodyModel::DefaultMaxVelocityY);
        }
        m_body->update(dt);
    }
    void BaseState::update(double dt)
    {
        const bool rightPressed = InputManager::Right.pressed();
        const bool leftPressed = InputManager::Left.pressed();
        if (rightPressed) {
            m_body->setForward(Forward::Right);
        } else if (leftPressed) {
            m_body->setForward(Forward::Left);
        }

        this->onMove(dt);

        // 攻撃
        if (m_charge->update(dt)) {
            double charge = m_charge->pop();
            m_pActor->getModule<World>()->create<Shot::ShotActor>(m_body->getPos() + Vec2{30 * m_body->getForward(), -1}, m_body->getForward(), charge);
            m_pActor->find<AttackCtrlModel>()->startAttack();
        }
        m_foot->reset();
    }
    void BaseState::onCollisionStay(IActor * col)
    {
        col->accept(overloaded{
            [this](const FloorActor& floor) {
                // 床
                this->onCollisionStay(floor);
            },
            [this](const LadderActor& ladder) {
                // 梯子
                this->onCollisionStay(ladder);
            },
            [this](const PenetrateFloorActor& floor) {
                // 貫通床
                this->onCollisionStay(floor);
            },
            [this](const DoorActor& door) {
                // 扉
                this->onCollisionStay(door);
            }
        });

        col->accept([this](const Attacker& attack) {
            if (m_hp->damage(attack.getPower())) {
                this->changeState(PlayerActor::State::Damage);
            }
        });
    }
    void BaseState::draw() const
    {
        auto view = m_pActor->getBindedView();
        if (!view) {
            return;
        }

        this->onDraw(*view);

        view->drawCharge();
        view->drawLight();
    }
}

#include "PlayerBaseState.hpp"
#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/views/Actors/Player/PlayerVM.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/commons/ActInclude.hpp>
#include <abyss/controllers/World/World.hpp>

namespace abyss
{
    ColDirection PlayerBaseState::fixPos(const MapColInfo& mapColInfo)
    {
        auto col = m_body->fixPos(mapColInfo);
        if (col.isUp()) {
            if (m_body->getVelocity().y > 0) {
                m_body->setVelocityY(0);
            }
            this->onLanding();
        }
        return col;
    }
    void PlayerBaseState::onCollisionStay(const FloorActor& col)
    {
        this->fixPos(col.getMapColInfo());
    }
    void PlayerBaseState::onCollisionStay(const PenetrateFloorActor& col)
    {
        this->fixPos(col.getMapColInfo());
    }
    void PlayerBaseState::onCollisionStay(const LadderActor & col)
    {
        if (col.isTop()) {
            this->fixPos(col.getMapColInfo());
        }
    }
    void PlayerBaseState::onCollisionStay([[maybe_unused]]const DoorActor & col)
    {}
    void PlayerBaseState::setup()
    {
        m_body = this->binded<BodyModel>();
        m_charge = this->binded<ChargeModel>();
    }
    void PlayerBaseState::start()
    {
        (*m_body)
            .setAccelY(BodyModel::DefaultGravity)
            .setVelocity({0, 0})
            .setMaxVelocityY(BodyModel::DefaultMaxVelocityY)
            .setDeccelX(180)
            .setMaxSpeedX(240);
    }
    void PlayerBaseState::onMove(double dt)
    {
        const bool rightPressed = InputManager::Right.pressed();
        const bool leftPressed = InputManager::Left.pressed();

        constexpr double Accel = 360;
        m_body->setAccelX(Accel * (rightPressed - leftPressed));
        // ジャンプ
        constexpr double JumpPower = 360;
        if (InputManager::Jump.down()) {
            m_body->jump(JumpPower);
        }
        if (InputManager::Down.pressed()) {
            m_body->setMaxVelocityY(Constants::Player::DiveSpeed * 60);
        } else {
            m_body->setMaxVelocityY(BodyModel::DefaultMaxVelocityY);
        }
        m_body->update(dt);
    }
    void PlayerBaseState::update(double dt)
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
            m_actor->getWorld()->create<PlayerShotActor>(m_body->getPos(), m_body->getForward(), charge);
        }
    }
    void PlayerBaseState::onCollisionStay(ICollider * col)
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
    }
    void PlayerBaseState::draw() const
    {
        auto view = m_actor->getBindedView();
        if (!view) {
            return;
        }

        this->onDraw(*view);

        view->drawCharge();
        view->drawLight();
    }
}

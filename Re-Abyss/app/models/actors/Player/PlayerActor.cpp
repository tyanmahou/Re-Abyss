#include "PlayerActor.hpp"
#include <abyss/models/actors/Player/Shot/PlayerShotActor.hpp>
#include <abyss/models/actors/PenetrateFloor/PenetrateFloorActor.hpp>
#include <abyss/models/actors/Ladder/LadderActor.hpp>
#include <abyss/models/actors/Door/DoorActor.hpp>

#include <abyss/models/World/WorldModel.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/utils/Collision.hpp>

namespace abyss
{
    bool PlayerActor::attack()
    {
        constexpr Key input = KeyX;

        if (input.down()) {
            // チャージなし
            return true;
        }

        // チャージ
        if (input.pressed()) {
            if (++m_charge >= Constants::Player::BigCharge) {
                m_charge = Constants::Player::BigCharge;
            }
            return false;
        }

        // チャージショット
        if (!input.pressed() && m_charge > 0) {
            return m_charge >= Constants::Player::SmallCharge;
        }

        m_charge = 0;
        return false;
    }
    void PlayerActor::nomarlMove()
    {
        const bool rightPressed = KeyRight.pressed();
        const bool leftPressed = KeyLeft.pressed();

        constexpr double Accel = 0.1;
        m_body.accel.x = Accel * (rightPressed - leftPressed);

        // ジャンプ
        constexpr double JumpPower = -6;
        if (KeyZ.down()) {
            m_body.vellocity.y = JumpPower;
        }

        m_body.vellocity += m_body.accel;

        if (m_body.vellocity.x > Constants::Player::MaxSpeed) {
            m_body.vellocity.x = Constants::Player::MaxSpeed;
        } else if (m_body.vellocity.x < -Constants::Player::MaxSpeed) {
            m_body.vellocity.x = -Constants::Player::MaxSpeed;
        } else if ((KeyRight.pressed() - KeyLeft.pressed()) == 0) {
            if (m_body.vellocity.x > 0) {
                m_body.vellocity.x -= 0.05;
            } else if (m_body.vellocity.x < 0) {
                m_body.vellocity.x += 0.05;
            }
            if (Abs(m_body.vellocity.x) < 0.01) {
                m_body.vellocity.x = 0;
            }
        }
        if (m_body.vellocity.y > Constants::Player::MaxGravity) {
            m_body.vellocity.y = Constants::Player::MaxGravity;
        }
        if (KeyDown.pressed()) {
            m_body.vellocity.y = Constants::Player::DiveSpeed;
        }
        m_body.pos += m_body.vellocity;
    }
    void PlayerActor::ladderMove()
    {
        m_body.vellocity = { 0,0 };
        m_body.pos.y += 2.0 * (KeyDown.pressed() - KeyUp.pressed());
        if (KeyZ.down()) {
            m_ladderState = LadderState::None;
        }
    }

    PlayerActor::PlayerActor() :
        m_charge(0),
        m_ladderState(LadderState::None)
    {
        this->tag = U"player";
        m_body.accel.y = 0.2;
        m_body.forward = Forward::Right;
    }

    void PlayerActor::update([[maybe_unused]]double dt)
    {
        const Vec2 prevPos = m_body.pos;

        const bool rightPressed = KeyRight.pressed();
        const bool leftPressed = KeyLeft.pressed();
        if (rightPressed) {
            m_body.forward = Forward::Right;
        } else if (leftPressed) {
            m_body.forward = Forward::Left;
        }

        if (this->m_ladderState) {
            this->ladderMove();
        } else {
            this->nomarlMove();
        }
        // 攻撃
        if (this->attack()) {
            m_pWorld->create<PlayerShotActor>(m_body.pos, m_body.forward, m_charge);
            m_charge = 0;
        }

        m_ladderState.reset();

        // モーション
        if (m_ladderState) {
            if (m_ladderState.isLadderTop()) {
                m_motion = Motion::LadderTop;
            } else {
                m_motion = Motion::Ladder;
            }
        } else {
            m_motion = Motion::Float;
            if (rightPressed || leftPressed) {
                m_motion = Motion::Swim;
            }
            if (m_body.vellocity.y > Constants::Player::MaxGravity) {
                m_motion = Motion::Dive;
            }

            if (KeyD.down()) {
                m_body.vellocity = { m_body.forward == Forward::Left ? 3.5 : -3.5,-3.5 };
            }
            if (KeyD.pressed()) {
                m_motion = Motion::Damge;
            }
        }
    }

    void PlayerActor::setPos(const Vec2& pos)
    {
        m_body.pos = pos;
    }

    const Vec2& PlayerActor::getPos() const
    {
        return m_body.pos;
    }

    const Vec2& PlayerActor::getVellocity() const
    {
        return m_body.vellocity;
    }

    void PlayerActor::setMotion(Motion motion)
    {
        m_motion = motion;
    }

    PlayerActor::Motion PlayerActor::getMotion() const
    {
        return m_motion;
    }

    Forward PlayerActor::getForward() const
    {
        return m_body.forward;
    }

    int32 PlayerActor::getCharge() const
    {
        return m_charge;
    }

    CShape PlayerActor::getCollider() const
    {
        return this->region();
    }

    ColDirection PlayerActor::collisionAndUpdateMotion(const RectF& region, ColDirection col)
    {
        auto collision = collision::Collision(region, this->region(), col);
        m_body.pos = collision.first;

        if (collision.second.isUp()) {
            if (m_motion == Motion::Float && m_body.vellocity.x == 0) {
                m_motion = Motion::Stay;
            } else if (m_motion == Motion::Swim && Abs(m_body.vellocity.x) > 1.5) {
                m_motion = Motion::Run;
            }
            if (m_body.vellocity.y > 0) {
                m_body.vellocity.y = 0;
            }
            if (m_ladderState.isLadder()) {
                m_ladderState.state = LadderState::None;
            }
        }
        return collision.second;
    }
    void PlayerActor::onCollisionStay(ICollider* col)
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

    void PlayerActor::onCollisionStay(const FloorActor& col)
    {
        auto c = col.getCol();
        c.ignoredForVelocity(m_body.vellocity);

        this->collisionAndUpdateMotion(col.region(), c);
    }
    void PlayerActor::onCollisionStay(const LadderActor& ladder)
    {
        if (ladder.isTop()) {
            auto&& ladderRegion = ladder.region();
            if (!m_ladderState) {
                this->collisionAndUpdateMotion(ladderRegion, ColDirection::Up);
            } else {
                static int ladderTopTimer = 0;
                //上端にきたら状態を繊維する
                if (m_body.pos.y <= ladderRegion.y) {
                    if (!m_ladderState.isLadderTop()) {
                        ladderTopTimer = 0;
                        m_ladderState.setLadderTop();
                        m_motion = Motion::LadderTop;
                    }
                    m_body.pos.y = ladderRegion.y;
                } else {
                    m_ladderState.cancelLadderTop();
                }
                if (m_ladderState.isLadderTop() && KeyUp.pressed()) {
                    ++ladderTopTimer;
                }
                if (m_ladderState.isLadderTop() && (KeyUp.down() || ladderTopTimer > 5)) {
                    m_body.pos.y = ladderRegion.y - this->region().h / 2.0;
                    m_ladderState = LadderState::None;
                    ladderTopTimer = 0;
                }
            }
        }
        if (ladder.getCenterLine().intersects(this->region())) {
            m_ladderState.setCanLadder();

            if (!m_ladderState.isLadder() && // 梯子状態じゃない
                (!ladder.isTop() && KeyUp.down() || KeyDown.down()) // 上下押した
            ) {
                m_ladderState.setIsLadder();
                m_motion = Motion::Ladder;
                m_body.pos.x = ladder.getPos().x;
                m_body.pos.y -= 2 * (KeyUp.down() - KeyDown.down());
            }
        }
    }
    void PlayerActor::onCollisionStay(const PenetrateFloorActor& col)
    {
        auto c = col.getCol();
        if (m_body.vellocity.y < 0) {
            c.ignored(ColDirection::Up);
        }
        auto colDirection = this->collisionAndUpdateMotion(col.region(), c);
        if (colDirection.isUp() && col.canDown() && KeyDown.down()) {
            // 降りる
            m_body.pos.y += 10.0;
        }
    }
    void PlayerActor::onCollisionStay(const DoorActor& door)
    {
        if (KeyUp.down()) {
            // move door
            m_motion = Motion::Door;
            m_body.vellocity = Vec2::Zero();
            //this->onIntoDoor().notify(&door);
        }
    }
    RectF PlayerActor::region() const
    {
        const Vec2 size = { 22, 80 };
        return { m_body.pos - size / 2, size };
    }
    void PlayerActor::accept(const ActVisitor& visitor)
    {
        visitor.visit(*this);
    }
    std::shared_ptr<PlayerActor> PlayerActor::Create()
    {
        return std::make_shared<PlayerActor>();
    }
}

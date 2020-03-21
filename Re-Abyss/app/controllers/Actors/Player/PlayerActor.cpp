#include <abyss/commons/ActInclude.hpp>

#include <abyss/controllers/World/World.hpp>
#include <abyss/controllers/ActionSystem/ActionSystem.hpp>

#include <abyss/commons/Constants.hpp>
#include <abyss/utils/Collision/Collision.hpp>
#include <abyss/commons/InputManager/InputManager.hpp>

namespace abyss
{
    bool PlayerActor::attack()
    {
        const auto& input = InputManager::Attack;

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
    void PlayerActor::nomarlMove(double dt)
    {
        const bool rightPressed = InputManager::Right.pressed();
        const bool leftPressed = InputManager::Left.pressed();

        constexpr double Accel = 0.1 * 3600;
        m_body.setAccelX(Accel * (rightPressed - leftPressed));
        // ジャンプ
        constexpr double JumpPower = 6 * 60;
        if (InputManager::Jump.down()) {
            m_body.jump(JumpPower);
        }
        if (InputManager::Down.pressed()) {
            m_body.setMaxVelocityY(Constants::Player::DiveSpeed * 60);
        } else {
            m_body.setMaxVelocityY(BodyModel::DefaultMaxVelocityY);
        }
        m_body.update(dt);
    }
    void PlayerActor::ladderMove()
    {
        m_body.setVelocity({ 0,0 });
        Vec2 pos = m_body.getPos();
        pos.y += 2.0 * (InputManager::Down.pressed() - InputManager::Up.pressed());
        m_body.setPos(pos);
        if (InputManager::A.down()) {
            m_ladderState = LadderState::None;
        }
    }

    PlayerActor::PlayerActor() :
        PlayerView(this),
        m_charge(0),
        m_ladderState(LadderState::None)
    {
        this->tag = U"player";
        m_body.setForward(Forward::Right).setDeccelX(180).setMaxSpeedX(240);
    }

    void PlayerActor::update([[maybe_unused]]double dt)
    {
        const Vec2 prevPos = m_body.getPos();

        const bool rightPressed = InputManager::Right.pressed();
        const bool leftPressed = InputManager::Left.pressed();
        if (rightPressed) {
            m_body.setForward(Forward::Right);
        } else if (leftPressed) {
            m_body.setForward(Forward::Left);
        }

        if (this->m_ladderState) {
            this->ladderMove();
        } else {
            this->nomarlMove(dt);
        }
        // 攻撃
        if (this->attack()) {
            m_pWorld->create<PlayerShotActor>(m_body.getPos(), m_body.getForward(), m_charge);
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
            if (m_body.getVelocity().y > Constants::Player::MaxGravity * 60) {
                m_motion = Motion::Dive;
            }
#if ABYSS_DEBUG
            if (KeyD.down()) {
                m_body.setVelocity({ m_body.getForward() == Forward::Left ? 3.5 : -3.5,-3.5 });
            }
            if (KeyD.pressed()) {
                m_motion = Motion::Damge;
            }
#endif
        }
    }

    void PlayerActor::setPos(const Vec2& pos)
    {
        m_body.setPos(pos);
    }

    const Vec2& PlayerActor::getPos() const
    {
        return m_body.getPos();
    }

    const Vec2& PlayerActor::getVellocity() const
    {
        return m_body.getVelocity();
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
        return m_body.getForward();
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
        auto collision = collision::CollisionByPrevPos(region, this->region(), m_body.getPrevPos(), col);
        m_body.setPos(collision.first);

        if (collision.second.isUp()) {
            if (m_motion == Motion::Float && m_body.getVelocity().x == 0) {
                m_motion = Motion::Stay;
            } else if (m_motion == Motion::Swim && Abs(m_body.getVelocity().x) > 1.5) {
                m_motion = Motion::Run;
            }
            if (m_body.getVelocity().y > 0) {
                m_body.setVelocityY(0);
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
        c.ignoredForVelocity(m_body.getVelocity());

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
                if (m_body.getPos().y <= ladderRegion.y) {
                    if (!m_ladderState.isLadderTop()) {
                        ladderTopTimer = 0;
                        m_ladderState.setLadderTop();
                        m_motion = Motion::LadderTop;
                    }
                    m_body.setPosY(ladderRegion.y);
                } else {
                    m_ladderState.cancelLadderTop();
                }
                if (m_ladderState.isLadderTop() && InputManager::Up.pressed()) {
                    ++ladderTopTimer;
                }
                if (m_ladderState.isLadderTop() && (InputManager::Up.down() || ladderTopTimer > 5)) {
                    m_body.setPosY(ladderRegion.y - this->region().h / 2.0);
                    m_ladderState = LadderState::None;
                    ladderTopTimer = 0;
                }
            }
        }
        if (ladder.getCenterLine().intersects(this->region())) {
            m_ladderState.setCanLadder();

            if (!m_ladderState.isLadder() && // 梯子状態じゃない
                (!ladder.isTop() && InputManager::Up.down() || InputManager::Down.down()) // 上下押した
            ) {
                m_ladderState.setIsLadder();
                m_motion = Motion::Ladder;
                m_body.setPosX(ladder.getPos().x);
                m_body.addPosY(-2 * (InputManager::Up.down() - InputManager::Down.down()));
            }
        }
    }
    void PlayerActor::onCollisionStay(const PenetrateFloorActor& col)
    {
        auto c = col.getCol();
        if (m_body.getVelocity().y < 0) {
            c.ignored(ColDirection::Up);
        }
        const auto& region = col.region();
        auto colDirection = this->collisionAndUpdateMotion(region, c);
        if (colDirection.isUp() && 
            col.tryDown(this->region()) &&
            InputManager::Down.down()
        ) {
            // 降りる
            m_body.addPosY(10.0);
        }
    }
    void PlayerActor::onCollisionStay(const DoorActor& door)
    {
        if (InputManager::Up.down()) {
            // move door
            m_motion = Motion::Door;
            m_body.setVelocity(Vec2::Zero());
            ActionSystem::Camera()->startDoorCameraWork(door, m_body.getPos(), [this]() {
                this->m_motion = Motion::Stay;
            });
        }
    }
    RectF PlayerActor::region() const
    {
        const Vec2 size = { 22, 80 };
        return { m_body.getPos() - size / 2, size };
    }
    void PlayerActor::accept(const ActVisitor& visitor)
    {
        visitor.visit(*this);
    }
    void PlayerActor::draw() const
    {
        PlayerView::draw();
    }
    std::shared_ptr<PlayerActor> PlayerActor::Create()
    {
        return std::make_shared<PlayerActor>();
    }
}

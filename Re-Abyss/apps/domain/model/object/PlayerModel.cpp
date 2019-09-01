#include "PlayerModel.hpp"
#include "PlayerShotModel.hpp"
#include "PenetrateFloorModel.hpp"
#include "LadderModel.hpp"
#include "DoorModel.hpp"

#include <domain/usecase/WorldUseCase.hpp>
#include <domain/visitor/WorldVisitor.hpp>
#include <application/common/Constants.hpp>

namespace abyss
{
	bool PlayerModel::attack()
	{
		constexpr Key input = Input::KeyX;

		if (input.clicked) {
			// チャージなし
			return true;
		}

		// チャージ
		if (input.pressed) {
			if (++m_charge >= Constants::Player::BigCharge) {
				m_charge = Constants::Player::BigCharge;
			}
			return false;
		}

		// チャージショット
		if (!input.pressed && m_charge > 0) {
			return m_charge >= Constants::Player::SmallCharge;
		}

		m_charge = 0;
		return false;
	}
	void PlayerModel::nomarlMove()
	{
		const bool rightPressed = Input::KeyRight.pressed;
		const bool leftPressed = Input::KeyLeft.pressed;

		constexpr double Accel = 0.1;
		m_body.accel.x = Accel * (rightPressed - leftPressed);

		// ジャンプ
		constexpr double JumpPower = -6;
		if (Input::KeyZ.clicked) {
			m_body.vellocity.y = JumpPower;
		}

		m_body.vellocity += m_body.accel;

		if (m_body.vellocity.x > Constants::Player::MaxSpeed) {
			m_body.vellocity.x = Constants::Player::MaxSpeed;
		}
		else if (m_body.vellocity.x < -Constants::Player::MaxSpeed) {
			m_body.vellocity.x = -Constants::Player::MaxSpeed;
		}
		else if ((Input::KeyRight.pressed - Input::KeyLeft.pressed) == 0) {
			if (m_body.vellocity.x > 0) {
				m_body.vellocity.x -= 0.05;
			}
			else if (m_body.vellocity.x < 0) {
				m_body.vellocity.x += 0.05;
			}
			if (Abs(m_body.vellocity.x) < 0.01) {
				m_body.vellocity.x = 0;
			}
		}
		if (m_body.vellocity.y > Constants::Player::MaxGravity) {
			m_body.vellocity.y = Constants::Player::MaxGravity;
		}
		if (Input::KeyDown.pressed) {
			m_body.vellocity.y = Constants::Player::DiveSpeed;
		}
		m_body.pos += m_body.vellocity;
	}
	void PlayerModel::ladderMove()
	{
		m_body.vellocity = { 0,0 };
		m_body.pos.y += 2.0 * (Input::KeyDown.pressed - Input::KeyUp.pressed);
		if (Input::KeyZ.clicked)
		{
			m_ladderState = LadderState::None;
		}
	}

	PlayerModel::PlayerModel() :
		m_charge(0),
		m_ladderState(LadderState::None)
	{
		this->tag = L"player";
		m_body.accel.y = 0.2;
		m_body.forward = Forward::Right;
	}

	void PlayerModel::update(double /*dt*/)
	{
		const Vec2 prevPos = m_body.pos;

		const bool rightPressed = Input::KeyRight.pressed;
		const bool leftPressed = Input::KeyLeft.pressed;
		if (rightPressed)
		{
			m_body.forward = Forward::Right;
		}
		else if (leftPressed)
		{
			m_body.forward = Forward::Left;
		}

		if (this->m_ladderState) {
			this->ladderMove();
		}
		else {
			this->nomarlMove();
		}
		// 攻撃
		if (this->attack()) {
			m_pWorld->createObject<PlayerShotModel>(m_body.pos, m_body.forward, m_charge);
			m_charge = 0;
		}

		m_ladderState.reset();

		// モーション
		if (m_ladderState) {
			if (m_ladderState.isLadderTop()) {
				m_motion = Motion::LadderTop;
			}
			else {
				m_motion = Motion::Ladder;
			}
		}
		else {
			m_motion = Motion::Float;
			if (rightPressed || leftPressed)
			{
				m_motion = Motion::Swim;
			}
			if (m_body.vellocity.y > Constants::Player::MaxGravity) {
				m_motion = Motion::Dive;
			}

			if (Input::KeyD.clicked)
			{
				m_body.vellocity = { m_body.forward == Forward::Left ? 3.5 : -3.5,-3.5 };
			}
			if (Input::KeyD.pressed) {
				m_motion = Motion::Damge;
			}
		}
	}

	void PlayerModel::setPos(const Vec2& pos)
	{
		m_body.pos = pos;
	}

	const Vec2& PlayerModel::getPos() const
	{
		return m_body.pos;
	}

	const Vec2& PlayerModel::getVellocity() const
	{
		return m_body.vellocity;
	}

	void PlayerModel::setMotion(Motion motion)
	{
		m_motion = motion;
	}

	PlayerModel::Motion PlayerModel::getMotion() const
	{
		return m_motion;
	}

	Forward PlayerModel::getForward() const
	{
		return m_body.forward;
	}

	int32 PlayerModel::getCharge() const
	{
		return m_charge;
	}

	CShape PlayerModel::getCollider() const
	{
		return this->region();
	}

	ColDirection PlayerModel::collisionAndUpdateMotation(const RectF& region, ColDirection col)
	{
		auto collision = collision::Collision(region, this->region(), col);
		m_body.pos = collision.first;

		if (collision.second & collision::Up) {
			if (m_motion == Motion::Float && m_body.vellocity.x == 0) {
				m_motion = Motion::Stay;
			}
			else if (m_motion == Motion::Swim && Abs(m_body.vellocity.x) > 1.5) {
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
	void PlayerModel::onCollisionStay(ICollider* col)
	{
		col->accept(overloaded{
			[this](const FloorModel& floor) {
				// 床
				this->onCollisionStay(floor);
			},
			[this](const LadderModel& ladder) {
				// 梯子
				this->onCollisionStay(ladder);
			},
			[this](const PenetrateFloorModel& floor) {
				// 貫通床
				this->onCollisionStay(floor);
			},
			[this](const DoorModel& door) {
				// 扉
				this->onCollisionStay(door);
			}
		});
	}
	void PlayerModel::onCollisionStay(const FloorModel& col)
	{
		auto c = col.getCol();
		if (m_body.vellocity.y > 0) c &= ~collision::Down;
		if (m_body.vellocity.y < 0) c &= ~collision::Up;
		if (m_body.vellocity.x > 0) c &= ~collision::Right;
		if (m_body.vellocity.x < 0) c &= ~collision::Left;

		this->collisionAndUpdateMotation(col.region(), c);
	}
	void PlayerModel::onCollisionStay(const LadderModel& ladder)
	{
		if (ladder.isTop()) {
			auto&& ladderRegion = ladder.region();
			if (!m_ladderState) {
				this->collisionAndUpdateMotation(ladderRegion, collision::Up);
			}
			else {
				static int ladderTopTimer = 0;
				//上端にきたら状態を繊維する
				if (m_body.pos.y <= ladderRegion.y) {
					if (!m_ladderState.isLadderTop()) {
						ladderTopTimer = 0;
						m_ladderState.setLadderTop();
						m_motion = Motion::LadderTop;
					}
					m_body.pos.y = ladderRegion.y;
				}
				else {
					m_ladderState.cancelLadderTop();
				}
				if (m_ladderState.isLadderTop() && Input::KeyUp.pressed) {
					++ladderTopTimer;
				}
				if (m_ladderState.isLadderTop() && (Input::KeyUp.clicked || ladderTopTimer > 5)) {
					m_body.pos.y = ladderRegion.y - this->region().h / 2.0;
					m_ladderState = LadderState::None;
					ladderTopTimer = 0;
				}
			}
		}
		if (ladder.getCenterLine().intersects(this->region())) {
			m_ladderState.setCanLadder();

			if (!m_ladderState.isLadder() && // 梯子状態じゃない
				(!ladder.isTop() && Input::KeyUp.clicked || Input::KeyDown.clicked) // 上下押した
				) {
				m_ladderState.setIsLadder();
				m_motion = Motion::Ladder;
				m_body.pos.x = ladder.getPos().x;
				m_body.pos.y -= 2 * (Input::KeyUp.clicked - Input::KeyDown.clicked);
			}
		}
	}
	void PlayerModel::onCollisionStay(const PenetrateFloorModel& col)
	{
		auto c = col.getCol();
		if (m_body.vellocity.y < 0) c &= ~collision::Up;

		auto colDirection = this->collisionAndUpdateMotation(col.region(), c);
		if ((colDirection & collision::Up) && col.canDown() && Input::KeyDown.clicked) {
			// 降りる
			m_body.pos.y += 10.0;
		}
	}
	void PlayerModel::onCollisionStay(const DoorModel& door)
	{
		if (Input::KeyUp.clicked) {
			// move door
			m_motion = Motion::Door;
			m_body.vellocity = Vec2::Zero;
			m_pWorld->notifyIntoDoor(this, door);
		}
	}
	RectF PlayerModel::region() const
	{
		const Vec2 size = { 22, 80 };
		return { m_body.pos - size / 2, size };
	}
	void PlayerModel::accept(const WorldVisitor& visitor)
	{
		visitor.visit(*this);
	}
}

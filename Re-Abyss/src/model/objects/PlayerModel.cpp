#include "PlayerModel.hpp"
#include "PlayerShotModel.hpp"
#include "FloorModel.hpp"
#include "../WorldModel.hpp"
#include "../Collision.hpp"
#include "../../common/Constants.hpp"

#include "../../util/TexturePacker.hpp"
#include "../../util/Periodic.hpp"
namespace
{
	using namespace abyss;

	class PlayerView
	{
		TexturePacker m_texture;
	public:
		PlayerView() :
			m_texture(L"work/player/player.json")
		{}

		void draw(const PlayerModel* player) const
		{
			Vec2 pos = Math::Ceil(player->getPos());
			Vec2 v = player->getVellocity();
			int timer = System::FrameCount();

			bool isRight = player->getForward() == Forward::Right;

			switch (player->getMotion())
			{
			case PlayerModel::Motation::Stay: {
				int page = timer % 240 <= 10 ? 1 : 0;
				m_texture(L"player_stay.png", { isRight ? 40 : 0, 80 * page }, { 40, 80 }).drawAt(pos);
			}break;
			case PlayerModel::Motation::Float: {
				double y = 160;
				if (v.y < -1.6) {
					y = 0;
				}
				else if (v.y < -0.8) {
					y = 80;
				}

				m_texture(L"player_float.png", { isRight ? 60 : 0, y }, { 60, 80 }).drawAt(pos);
			}break;
			case PlayerModel::Motation::Swim: {
				double y = 0;
				if (v.y < -1.6) {
					y = 160;
				}
				else if (v.y < -0.8) {
					y = 240;
				}
				else {
					y = 80 * (timer / 30 % 2);
				}
				m_texture(L"player_swim.png", { isRight ? 60 : 0, y }, { 60, 80 }).drawAt(pos);
			}break;
			case PlayerModel::Motation::Dive: {
				double y = 80 * (timer / 30 % 2);
				m_texture(L"player_dive.png", { isRight ? 60 : 0, y }, { 60, 80 }).drawAt(pos);
			}break;
			case PlayerModel::Motation::Damge: {
				Color c = timer / 6 % 2 ? Color(255, 128, 128, 128) : Palette::White;
				m_texture(L"player_damage.png", { isRight ? 60 : 0, 0 }, { 60, 80 }).drawAt(pos, c);
			}break;
			default:
				break;
			}

			// チャージ
			int32 charge = player->getCharge();
			if (charge > 10) {
				Graphics2D::SetBlendState(BlendState::Additive);
				double a = 0.5 * Periodic::Triangle0_1(0.2s);
				ColorF color = charge >= Constants::Player::BigCharge ? Constants::Player::BigChargeColorBase :
					charge >= Constants::Player::MediumCharge ? Constants::Player::MediumChargeColorBase :
					ColorF(1);
				Circle(pos, 80 * (1 - Periodic::Sawtooth0_1(0.6s))).drawFrame(1, 1, color.setAlpha(a));
				double s = 100 * Periodic::Triangle0_1(0.3s);
				RectF({ 0,0,s, s })
					.setCenter(pos)
					.rotated(Math::QuarterPi * Periodic::Square0_1(0.6s))
					.drawFrame(1, 1, color.setAlpha(0.5 - a));

				if (charge >= Constants::Player::BigCharge) {
					Circle(pos, Periodic::Triangle0_1(0.3s) * 30 + 30).draw(color.setAlpha(a));
				}
				else if (charge >= Constants::Player::MediumCharge) {
					Circle(pos, Periodic::Triangle0_1(0.3s) * 5 + 30).draw(color.setAlpha(a));
				}
				Graphics2D::SetBlendState(BlendState::Default);
			}
		}
	};
}
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
		if (input.released) {
			return m_charge >= Constants::Player::SmallCharge;
		}

		m_charge = 0;
		return false;
	}
	PlayerModel::PlayerModel() :
		m_charge(0)
	{
		this->tag = L"player";
		m_body.accel.y = 0.2;
		m_body.forward = Forward::Right;
	}

	void PlayerModel::update(double /*dt*/)
	{
		const bool rightPressed = Input::KeyRight.pressed;
		const bool leftPressed = Input::KeyLeft.pressed;
		const Vec2 prevPos = m_body.pos;
		if (rightPressed)
		{
			m_body.forward = Forward::Right;
		}
		else if (leftPressed)
		{
			m_body.forward = Forward::Left;
		}

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

		// 攻撃
		if(this->attack()){
			m_pWorld->createObject<PlayerShotModel>(m_body.pos, m_body.forward, m_charge);
			m_charge = 0;
		}

		// モーション
		m_motation = Motation::Float;
		if (rightPressed || leftPressed)
		{
			m_motation = Motation::Swim;
		}
		if (m_body.vellocity.y > Constants::Player::MaxGravity) {
			m_motation = Motation::Dive;
		}

		if (Input::KeyD.clicked)
		{
			m_body.vellocity = { m_body.forward == Forward::Left ? 3.5 : -3.5,-3.5 };
		}
		if (Input::KeyD.pressed) {
			m_motation = Motation::Damge;
		}
	}
	void PlayerModel::draw() const
	{
		static PlayerView view;

		view.draw(this);
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

	PlayerModel::Motation PlayerModel::getMotion() const
	{
		return m_motation;
	}

	Forward PlayerModel::getForward() const
	{
		return m_body.forward;
	}

	int32 PlayerModel::getCharge() const
	{
		return m_charge;
	}

	Shape PlayerModel::getCollider() const
	{
		return static_cast<Shape>(this->region());
	}
	void PlayerModel::onCollisionStay(ICollider* col)
	{
		if (col->getTag() == L"floor") {
			auto* floor = static_cast<FloorModel*>(col);
			auto c = floor->getCol();
			if (m_body.vellocity.y > 0) c &= ~collision::Down;
			if (m_body.vellocity.y < 0) c &= ~collision::Up;
			if (m_body.vellocity.x > 0) c &= ~collision::Right;
			if (m_body.vellocity.x < 0) c &= ~collision::Left;

			auto collision = collision::Collision(floor->region(), this->region(), c);
			m_body.pos = collision.first;

			if (collision.second & collision::Up) {
				if (m_motation == Motation::Float && m_body.vellocity.x == 0) {
					m_motation = Motation::Stay;
				}
				if (m_body.vellocity.y > 0) {
					m_body.vellocity.y = 0;
				}
			}
		}
	}
	RectF PlayerModel::region() const
	{
		const Vec2 size = { 22, 80 };
		return { m_body.pos - size / 2, size };
	}
}

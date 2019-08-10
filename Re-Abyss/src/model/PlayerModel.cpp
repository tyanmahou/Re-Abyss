#include "PlayerModel.hpp"
#include "../util/TexturePacker.hpp"

namespace
{
	using namespace abyss;

	constexpr double maxGravity = 1.3;
	constexpr double diveSpeed = 2.2;
	constexpr double maxSpeed = 4;

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
				int page = timer / 240 % 2;
				m_texture(L"player_stay.png", { isRight ? 40 : 0, 80*page }, { 40, 80 }).drawAt(pos);
			}break;
			case PlayerModel::Motation::Float: {
				double y = 160;
				if (v.y < -1.6) {
					y = 0;
				}
				else if(v.y < -0.8){
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
					y = 80 * (timer / 60 % 2);
				}
				m_texture(L"player_swim.png", { isRight ? 60 : 0, y }, { 60, 80 }).drawAt(pos);
			}break;
			case PlayerModel::Motation::Damge: {
				m_texture(L"player_damage.png", { isRight ? 60 : 0, 0 }, { 60, 80 }).drawAt(pos);
			}break;
			default:
				break;
			}
		}
	};
}
namespace abyss
{
	PlayerModel::PlayerModel()
	{
		this->tag = L"player";
		m_body.accel.y = 0.2;
	}

	void PlayerModel::update(double /*dt*/)
	{
		const Vec2 prevPos = m_body.pos;
		if (Input::KeyRight.pressed)
		{
			m_forward = Forward::Right;
		}
		else if (Input::KeyLeft.pressed)
		{
			m_forward = Forward::Left;
		}

		constexpr double Accel = 0.1;
		m_body.accel.x = Accel * (Input::KeyRight.pressed - Input::KeyLeft.pressed);

		// ƒWƒƒƒ“ƒv
		constexpr double JumpPower = -6;
		if (Input::KeyZ.clicked) {
			m_body.vellocity.y = JumpPower;
		}

		m_body.vellocity += m_body.accel;

		if (m_body.vellocity.x > maxSpeed) {
			m_body.vellocity.x = maxSpeed;
		}
		else if (m_body.vellocity.x < - maxSpeed) {
			m_body.vellocity.x = -maxSpeed;
		}
		else if ((Input::KeyRight.pressed - Input::KeyLeft.pressed) == 0){
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
		if (m_body.vellocity.y > maxGravity) {
			m_body.vellocity.y = maxGravity;
		}
		if (Input::KeyDown.pressed) {
			m_body.vellocity.y = diveSpeed;
		}
		m_body.pos += m_body.vellocity;

		m_motation = Motation::Float;
		if (Abs(m_body.pos.x - prevPos.x))
		{
			m_motation = Motation::Swim;
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
		return m_forward;
	}

	Shape PlayerModel::getCollider() const
	{
		return static_cast<Shape>(Ellipse(m_body.pos, { 18,40 }));
	}
}

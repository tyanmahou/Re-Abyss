#include "PlayerView.hpp"
#include "../../../domain/model/object/PlayerModel.hpp"
#include "../../../application/common/Constants.hpp"
#include "../../../application/util/Periodic.hpp"

#include <Siv3D.hpp>

namespace abyss
{
	void PlayerView::drawPlayer() const
	{
		auto pPlayer = m_pPlayer.lock();

		Vec2 pos = Math::Ceil(pPlayer->getPos());
		Vec2 v = pPlayer->getVellocity();
		int timer = System::FrameCount();

		bool isRight = pPlayer->getForward() == Forward::Right;

		switch (pPlayer->getMotion())
		{
		case PlayerModel::Motion::Stay: {
			int page = timer % 240 <= 10 ? 1 : 0;
			m_texture(L"player_stay.png", { isRight ? 40 : 0, 80 * page }, { 40, 80 }).drawAt(pos);
		}break;
		case PlayerModel::Motion::Float: {
			double y = 160;
			if (v.y < -1.6) {
				y = 0;
			}
			else if (v.y < -0.8) {
				y = 80;
			}
			else {
				y = 80 * (timer / 30 % 2) + 160;
			}

			m_texture(L"player_float.png", { isRight ? 60 : 0, y }, { 60, 80 }).drawAt(pos);
		}break;
		case PlayerModel::Motion::Run: {
			int x = static_cast<int>(Periodic::Triangle0_1(1.2s) * 5) * 60;
			m_texture(L"player_run.png", { x, isRight ? 80 : 0 }, { 60, 80 }).drawAt(pos);
		}break;
		case PlayerModel::Motion::Swim: {
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
		case PlayerModel::Motion::Dive: {
			double y = 80 * (timer / 30 % 2);
			m_texture(L"player_dive.png", { isRight ? 60 : 0, y }, { 60, 80 }).drawAt(pos);
		}break;
		case PlayerModel::Motion::Damge: {
			Color c = timer / 6 % 2 ? Color(255, 128, 128, 128) : Palette::White;
			m_texture(L"player_damage.png", { isRight ? 60 : 0, 0 }, { 60, 80 }).drawAt(pos, c);
		}break;
		case PlayerModel::Motion::Ladder: {
			m_texture(L"player_ladder.png", { 40 * (static_cast<int>(pos.y / 30) % 2), 0 }, { 40, 80 }).drawAt(pos);
		}break;
		case PlayerModel::Motion::LadderTop: {
			m_texture(L"player_ladder.png", { 80, 0 }, { 40, 80 }).drawAt(pos);
		}break;
		case PlayerModel::Motion::Door: {

			m_texture(L"player_door.png", { 40 * static_cast<int>(Periodic::Sawtooth0_1(1s) * 2), 0 }, { 40, 80 }).drawAt(pos);
		}break;
		default:
			break;
		}
	}
	void PlayerView::drawCharge() const
	{
		auto pPlayer = m_pPlayer.lock();

		Vec2 pos = Math::Ceil(pPlayer->getPos());
		int32 charge = pPlayer->getCharge();

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
	PlayerView::PlayerView(std::shared_ptr<PlayerModel> pPlayer):
		m_texture(L"work/player/player.json"),
		m_pPlayer(pPlayer)
	{}
	void PlayerView::draw() const
	{
		this->drawPlayer();

		// ƒ`ƒƒ[ƒW
		this->drawCharge();
	}

	bool PlayerView::isDelete() const
	{
		return m_pPlayer.expired();
	}

}
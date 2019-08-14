#include "PlayerShotModel.hpp"
#include "../GameCamera.hpp"
#include "../../common/Constants.hpp"
#include "../WorldModel.hpp"
#include "../../view/effects/PlayerShotEffect.hpp"

#include <Siv3D.hpp>

namespace
{
	using namespace abyss;

	double TypeToR(PlayerShotModel::Type type)
	{
		static const std::unordered_map<PlayerShotModel::Type, double> rMap{
			{PlayerShotModel::Type::Normal, 5},
			{PlayerShotModel::Type::Small, 10},
			{PlayerShotModel::Type::Medium, 20},
			{PlayerShotModel::Type::Big, 30},
		};
		return rMap.at(type);
	}
	Color TypeToColor(PlayerShotModel::Type type)
	{
		using namespace Constants::Player;
		static const std::unordered_map<PlayerShotModel::Type, Color> colorMap{
			{PlayerShotModel::Type::Normal, ColorF(1)},
			{PlayerShotModel::Type::Small, ColorF(1)},
			{PlayerShotModel::Type::Medium, MediumChargeColorBase},
			{PlayerShotModel::Type::Big, BigChargeColorBase},
		};
		return colorMap.at(type);
	}
}
namespace abyss
{
	PlayerShotModel::PlayerShotModel(const s3d::Vec2& pos, Forward forward, s3d::int32 charge)
	{
		using namespace Constants::Player;
		m_body.pos = pos;
		m_body.forward = forward;

		constexpr double speed = 14;
		m_body.vellocity.x = forward == Forward::Right ? speed : -speed;
		if (charge >= BigCharge) {
			m_type = Type::Big;
		}
		else if (charge >= MediumCharge) {
			m_type = Type::Medium;
		}
		else if (charge >= SmallCharge) {
			m_type = Type::Small;
		}
		else {
			m_type = Type::Normal;
		}
	}
	void PlayerShotModel::start()
	{
		// effect
		if (m_type != Type::Normal) {
			m_pWorld->getEffect().add<PlayerShotFiringEffect>(m_body.pos, ::TypeToR(m_type), ::TypeToColor(m_type));
		}
	}
	void PlayerShotModel::update(double /*dt*/)
	{
		m_body.pos += m_body.vellocity;

		// effect
		if (System::FrameCount() % 2 && (m_type == Type::Big || m_type == Type::Medium)) {
			m_pWorld->getEffect().add<PlayerShotEffect>(m_body.pos, ::TypeToR(m_type), ::TypeToColor(m_type));
		}
		// âÊñ äOîªíË
		if (!GameCamera::Main()->carentRoom().getRegion().intersects(this->getColliderCircle())) {
			m_isActive = false;
		}
	}
	void PlayerShotModel::draw() const
	{
		this->getColliderCircle().draw();
	}
	s3d::Shape PlayerShotModel::getCollider() const
	{
		return static_cast<s3d::Shape>(this->getColliderCircle());
	}

	void PlayerShotModel::onCollisionStay(ICollider* col)
	{
		if (m_type != Type::Big && col->getTag() == L"floor") {
			// ï«Ç…ìñÇΩÇ¡Çƒè¡Ç¶ÇÈ
			m_isActive = false;
		}
	}

	bool PlayerShotModel::isDelete() const
	{
		return !m_isActive;
	}
	s3d::Circle PlayerShotModel::getColliderCircle() const
	{
		return s3d::Circle(m_body.pos, ::TypeToR(m_type));
	}
}
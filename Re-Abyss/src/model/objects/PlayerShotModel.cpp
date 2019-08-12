#include "PlayerShotModel.hpp"
#include "../GameCamera.hpp"
#include "../../common/Constants.hpp"

#include <Siv3D.hpp>

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
	void PlayerShotModel::update(double /*dt*/)
	{
		m_body.pos += m_body.vellocity;

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
		static const std::unordered_map<Type, double> rMap{
			{Type::Normal, 5},
			{Type::Small, 10},
			{Type::Medium, 20},
			{Type::Big, 30},
		};
		return s3d::Circle(m_body.pos, rMap.at(m_type));
	}
}
#include "PlayerShotModel.hpp"
#include "../../../application/common/Constants.hpp"
#include <domain/usecase/WorldUseCase.hpp>
#include <domain/model/CameraModel.hpp>
#include <unordered_map>

namespace
{
	using namespace abyss;

	double TypeToR(PlayerShotModel::Type type)
	{
		static const std::unordered_map<PlayerShotModel::Type, double> rMap{
			{PlayerShotModel::Type::Normal, 5},
			{PlayerShotModel::Type::Small, 8},
			{PlayerShotModel::Type::Medium, 16},
			{PlayerShotModel::Type::Big, 24},
		};
		return rMap.at(type);
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

	}
	void PlayerShotModel::update(double /*dt*/)
	{
		m_body.pos += m_body.vellocity;

		// âÊñ äOîªíË
		if (!m_pWorld->getCamera()->inRoom(this->getColliderCircle())) {
			m_isActive = false;
		}
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

	s3d::Circle PlayerShotModel::getColliderCircle() const
	{
		return s3d::Circle(m_body.pos, ::TypeToR(m_type));
	}
	PlayerShotModel::Type PlayerShotModel::getType() const
	{
		return m_type;
	}
	Forward PlayerShotModel::getForward() const
	{
		return m_body.forward;
	}
	const s3d::Vec2& PlayerShotModel::getPos() const
	{
		return m_body.pos;
	}
}
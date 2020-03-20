#include <abyss/commons/ActInclude.hpp>
#include <abyss/commons/Constants.hpp>
#include <unordered_map>

#include <abyss/controllers/World/World.hpp>
#include <abyss/controllers/ActionSystem/ActionSystem.hpp>

namespace
{
	using namespace abyss;

	double TypeToR(PlayerShotActor::Type type)
	{
		static const std::unordered_map<PlayerShotActor::Type, double> rMap{
			{PlayerShotActor::Type::Normal, 5},
			{PlayerShotActor::Type::Small, 8},
			{PlayerShotActor::Type::Medium, 16},
			{PlayerShotActor::Type::Big, 24},
		};
		return rMap.at(type);
	}
}
namespace abyss
{
	PlayerShotActor::PlayerShotActor(const s3d::Vec2& pos, Forward forward, s3d::int32 charge):
		PlayerShotView(this)
	{
		constexpr double speed = 14*60;

		using namespace Constants::Player;
		m_body
			.setPos(pos)
			.setForward(forward)
			.noneResistanced()
			.setVelocityX(forward == Forward::Right ? speed : -speed)
			;

		if (charge >= BigCharge) {
			m_type = Type::Big;
		} else if (charge >= MediumCharge) {
			m_type = Type::Medium;
		} else if (charge >= SmallCharge) {
			m_type = Type::Small;
		} else {
			m_type = Type::Normal;
		}
	}
	void PlayerShotActor::start()
	{
		PlayerShotView::start();
	}
	void PlayerShotActor::update([[maybe_unused]]double dt)
	{
		m_body.update(dt);

		// 画面外判定
		if (!ActionSystem::Camera()->inRoom(this->getColliderCircle())) {
			m_isActive = false;
		}
	}

	CShape PlayerShotActor::getCollider() const
	{
		return this->getColliderCircle();
	}

	void PlayerShotActor::onCollisionStay(ICollider* col)
	{
		if (m_type != Type::Big) {
			col->accept([this](FloorActor&) {
				// 壁に当たって消える
				m_isActive = false;
			});
		}
	}

	s3d::Circle PlayerShotActor::getColliderCircle() const
	{
		return s3d::Circle(m_body.getPos(), ::TypeToR(m_type));
	}
	PlayerShotActor::Type PlayerShotActor::getType() const
	{
		return m_type;
	}
	Forward PlayerShotActor::getForward() const
	{
		return m_body.getForward();
	}
	const s3d::Vec2& PlayerShotActor::getPos() const
	{
		return m_body.getPos();
	}
	void PlayerShotActor::accept(const ActVisitor& visitor)
	{
		visitor.visit(*this);
	}
	void PlayerShotActor::draw() const
	{
		PlayerShotView::draw();
	}
}
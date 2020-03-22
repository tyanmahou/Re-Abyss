#include <abyss/commons/ActInclude.hpp>
#include <abyss/views/Actors/Player/Shot/PlayerShotVM.hpp>
#include "State/PlayerShotBaseState.hpp"

namespace abyss
{
	PlayerShotActor::PlayerShotActor(const s3d::Vec2& pos, Forward forward, double charge):
		m_shot(charge),
		m_state(this)
	{
		m_state
			.add<PlayerShotBaseState>(State::Base)
			.bind<BodyModel>(&PlayerShotActor::m_body)
			.bind<PlayerShotModel>(&PlayerShotActor::m_shot);

		constexpr double speed = 14*60;
		m_body
			.setPos(pos)
			.setForward(forward)
			.noneResistanced()
			.setVelocityX(forward == Forward::Right ? speed : -speed)
			;
		m_view = std::make_shared<PlayerShotVM>(m_shot, forward);
	}
	void PlayerShotActor::start()
	{}
	void PlayerShotActor::update([[maybe_unused]]double dt)
	{
		m_state.update(dt);
	}

	CShape PlayerShotActor::getCollider() const
	{
		return this->getColliderCircle();
	}

	void PlayerShotActor::onCollisionStay(ICollider* col)
	{
		m_state.onCollisionStay(col);
	}

	s3d::Circle PlayerShotActor::getColliderCircle() const
	{
		return s3d::Circle(m_body.getPos(), m_shot.toRadius());
	}

	void PlayerShotActor::accept(const ActVisitor& visitor)
	{
		visitor.visit(*this);
	}
	void PlayerShotActor::draw() const
	{
		m_state.draw();
	}
	PlayerShotVM* PlayerShotActor::getBindedView() const
	{
		if (!m_view) {
			return nullptr;
		}
		return &m_view->setPos(m_body.getPos());
	}
}
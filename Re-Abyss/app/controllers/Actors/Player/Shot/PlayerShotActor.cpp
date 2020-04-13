#include <abyss/views/Actors/Player/Shot/PlayerShotVM.hpp>
#include <abyss/commons/LayerGroup.hpp>
#include "State/PlayerShotBaseState.hpp"
#include <abyss/params/Actors/Player/PlayerShotParam.hpp>

namespace abyss
{
	PlayerShotActor::PlayerShotActor(const s3d::Vec2& pos, Forward forward, double charge):
		m_shot(charge),
		m_state(this)
	{
		this->layer = LayerGroup::Player;
		m_state
			.add<PlayerShotBaseState>(State::Base)
			.bind<BodyModel>(&PlayerShotActor::m_body)
			.bind<PlayerShotModel>(&PlayerShotActor::m_shot);

		m_body
			.setPos(pos)
			.setForward(forward)
			.noneResistanced()
			.setVelocityX(forward * PlayerShotParam::Base::Speed)
			;
		m_power = m_shot.toPower();
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

	bool PlayerShotActor::accept(const ActVisitor& visitor)
	{
		return visitor.visit(static_cast<Attacker&>(*this)) || 
			visitor.visit(static_cast<IActor&>(*this));
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
		return &m_view->setPos(m_body.getPos()).setManager(m_pManager);
	}
}
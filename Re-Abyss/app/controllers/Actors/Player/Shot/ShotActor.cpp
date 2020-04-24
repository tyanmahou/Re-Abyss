#include <abyss/views/Actors/Player/Shot/ShotVM.hpp>
#include <abyss/commons/LayerGroup.hpp>
#include "State/BaseState.hpp"
#include <abyss/params/Actors/Player/ShotParam.hpp>

namespace abyss::Player::Shot
{
	ShotActor::ShotActor(const s3d::Vec2& pos, Forward forward, double charge):
		m_shot(charge),
		m_state(this)
	{
		this->layer = LayerGroup::Player;
		m_state
			.add<BaseState>(State::Base)
			.bind<BodyModel>(&ShotActor::m_body)
			.bind<PlayerShotModel>(&ShotActor::m_shot);

		m_body
			.setPos(pos)
			.setForward(forward)
			.noneResistanced()
			.setVelocityX(forward * ShotParam::Base::Speed)
			;
		m_power = m_shot.toPower();
		m_view = std::make_shared<ShotVM>(m_shot, forward);
	}
	void ShotActor::start()
	{}
	void ShotActor::update([[maybe_unused]]double dt)
	{
		m_state.update(dt);
	}

	CShape ShotActor::getCollider() const
	{
		return this->getColliderCircle();
	}

	void ShotActor::onCollisionStay(ICollider* col)
	{
		m_state.onCollisionStay(col);
	}

	s3d::Circle ShotActor::getColliderCircle() const
	{
		return s3d::Circle(m_body.getPos(), m_shot.toRadius());
	}

	bool ShotActor::accept(const ActVisitor& visitor)
	{
		return visitor.visit(static_cast<Attacker&>(*this)) || 
			visitor.visit(static_cast<IActor&>(*this));
	}
	void ShotActor::draw() const
	{
		m_state.draw();
	}
	ShotVM* ShotActor::getBindedView() const
	{
		if (!m_view) {
			return nullptr;
		}
		return &m_view->setPos(m_body.getPos()).setManager(m_pManager);
	}
}
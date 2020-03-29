#include "State/SlimeWalkState.hpp"
#include "State/SlimeJumpState.hpp"
#include "Senser/SlimeSenser.hpp"

#include <abyss/controllers/World/World.hpp>
#include <abyss/views/Actors/Slime/SlimeVM.hpp>

namespace abyss
{
	SlimeActor::SlimeActor(const s3d::Vec2& pos, Forward forward) :
		EnemyActor(pos, forward),
		m_view(std::make_shared<SlimeVM>()),
		m_state(this)
	{
		m_hp.setHp(6);
		m_body.setMaxSpeedX(60);

		m_state
			.add<SlimeWalkState>(State::Walk)
			.add<SlimeJumpState>(State::Jump)
			.bind<BodyModel>(&SlimeActor::m_body);
	}

	void SlimeActor::start()
	{
		if (!m_senser) {
			m_senser = m_pWorld->create<SlimeSenser>(this);
		}
	}

	void SlimeActor::update([[maybe_unused]]double dt)
	{
		m_state.update(dt);
	}

	void SlimeActor::draw() const
	{
		m_state.draw();
	}

	void SlimeActor::onCollisionStay(ICollider* col)
	{
		m_state.onCollisionStay(col);
	}

	bool SlimeActor::accept(const ActVisitor& visitor)
	{
		return visitor.visit(*this);
	}
	SlimeVM* SlimeActor::getBindedView() const
	{
		return &m_view->setForward(this->getForward())
			.setPos(this->getPos())
			.setVelocity(this->getVellocity())
			.setIsDamaging(this->m_hp.isInInvincibleTime())
			;
	}
	bool SlimeActor::isWalk() const
	{
		return m_state.getState() == State::Walk;
	}
	void SlimeActor::onDead()
	{
		m_senser->destroy();
	}
}
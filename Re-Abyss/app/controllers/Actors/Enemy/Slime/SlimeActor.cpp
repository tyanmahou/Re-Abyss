#include <abyss/models/Actors/Enemy/Slime/State/WalkState.hpp>
#include <abyss/models/Actors/Enemy/Slime/State/JumpState.hpp>
#include <abyss/models/Actors/Commons/DamageModel.hpp>

#include "Senser/Senser.hpp"

#include <abyss/controllers/World/World.hpp>
#include <abyss/entities/Actors/Enemy/SlimeEntity.hpp>
#include <abyss/views/Actors/Enemy/Slime/SlimeVM.hpp>
#include <abyss/params/Actors/Enemy/Slime/Param.hpp>
#include <abyss/models/Actors/Enemy/Slime/DeadCallbackModel.hpp>
#include <abyss/models/Actors/Enemy/Slime/SenserCtrlModel.hpp>

namespace abyss::Slime
{
	SlimeActor::SlimeActor(const SlimeEntity& entity) :
		EnemyActor(entity.pos, entity.forward),
		m_view(std::make_shared<SlimeVM>())
	{
		m_hp->setHp(Param::Base::Hp);
		m_body
			->setMaxSpeedX(Param::Walk::MaxSpeedX);
		m_state = this->attach<StateModel<SlimeActor>>(this);
		m_state
			->add<WalkState>(State::Walk)
			.add<JumpState>(State::Jump)
			;
		this->attach<DamageModel>(this);
		this->attach<DeadCallbackModel>(this);
		this->attach<SenserCtrlModel>();
	}

	void SlimeActor::start()
	{
		auto m_senser = getModule<World>()->create<Senser>(this);
		this->find<SenserCtrlModel>()->set(m_senser);
	}

	bool SlimeActor::accept(const ActVisitor& visitor)
	{
		return visitor.visit(*this);
	}
	SlimeVM* SlimeActor::getBindedView() const
	{
		return &m_view->setForward(this->getForward())
			.setPos(this->getPos())
			.setVelocity(this->getVelocity())
			.setIsDamaging(this->m_hp->isInInvincibleTime())
			;
	}
	bool SlimeActor::isWalk() const
	{
		return m_state->getState() == State::Walk;
	}
}
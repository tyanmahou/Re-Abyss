#include "SlimeActor.hpp"
#include "Senser/Senser.hpp"

#include <abyss/models/Actors/Enemy/Slime/State/WalkState.hpp>


#include <abyss/controllers/World/World.hpp>
#include <abyss/controllers/Actors/Enemy/EnemyBuilder.hpp>

#include <abyss/entities/Actors/Enemy/SlimeEntity.hpp>
#include <abyss/params/Actors/Enemy/Slime/Param.hpp>
#include <abyss/models/Actors/Enemy/Slime/DeadCallbackModel.hpp>
#include <abyss/models/Actors/Enemy/Slime/SenserCtrlModel.hpp>
#include <abyss/models/Actors/Enemy/Slime/DrawModel.hpp>

namespace abyss::Slime
{
	SlimeActor::SlimeActor(const SlimeEntity& entity)
	{
		Enemy::EnemyBuilder builder(this);

		builder
			.setInitPos(entity.pos)
			.setForward(entity.forward)
			.setInitHp(Param::Base::Hp)
			.setIsEnableRoomHit(true)
			.setAudioSettingGroupPath(U"Enemy/Slime/slime.aase")
			.setIsEnableDeadCallback(false)
			.setInitState<WalkState>()
			.build();
		{
			m_body
				->setMaxSpeedX(Param::Walk::MaxSpeedX);
		}
		{
			m_state = this->find<StateModel>();
		}

		this->attach<DeadCallbackModel>(this);
		this->attach<SenserCtrlModel>();
		this->attach<DrawModel>(this);
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
	bool SlimeActor::isWalk() const
	{
		return m_state->isState<WalkState>();
	}
}
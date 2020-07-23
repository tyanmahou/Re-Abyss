#include "SlimeActor.hpp"
#include "Senser/Senser.hpp"

#include <abyss/controllers/World/World.hpp>
#include <abyss/controllers/Actors/Enemy/EnemyBuilder.hpp>
#include <abyss/entities/Actors/Enemy/SlimeEntity.hpp>
#include <abyss/params/Actors/Enemy/Slime/Param.hpp>

#include <abyss/models/Actors/Commons/ViewModel.hpp>
#include <abyss/models/Actors/Enemy/Slime/DeadCallbackModel.hpp>
#include <abyss/models/Actors/Enemy/Slime/SenserCtrlModel.hpp>
#include <abyss/models/Actors/Enemy/Slime/State/WalkState.hpp>

#include <abyss/views/Actors/Enemy/Slime/SlimeVM.hpp>

namespace
{
	class ViewBinder;
}
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

		this->attach<ViewModel<SlimeVM>>()
			->createBinder<ViewBinder>(this);
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

namespace
{
	using namespace abyss;
	using namespace abyss::Slime;

	class ViewBinder : public ViewModel<SlimeVM>::IBinder
	{
		IActor* m_pActor = nullptr;
		Ref<BodyModel> m_body;
		Ref<HPModel> m_hp;
	private:
		SlimeVM* bind(SlimeVM* view) const
		{
			return &view->setTime(m_pActor->getDrawTimeSec())
				.setForward(m_body->getForward())
				.setPos(m_body->getPos())
				.setVelocity(m_body->getVelocity())
				.setIsDamaging(m_hp->isInInvincibleTime())
				;
		}
		void setup() override
		{
			m_body = m_pActor->find<BodyModel>();
			m_hp = m_pActor->find<HPModel>();
		}
	public:
		ViewBinder(IActor* pActor) :
			m_pActor(pActor)
		{}
	};
}
#include "SlimeActor.hpp"

#include <abyss/controllers/Actors/Enemy/EnemyBuilder.hpp>
#include <abyss/entities/Actors/Enemy/SlimeEntity.hpp>
#include <abyss/params/Actors/Enemy/Slime/Param.hpp>

#include <abyss/components/Actors/Commons/ViewCtrl.hpp>
#include <abyss/components/Actors/Enemy/Slime/DeadCallback.hpp>
#include <abyss/components/Actors/Enemy/Slime/SenserCtrl.hpp>
#include <abyss/components/Actors/Enemy/Slime/State/WalkState.hpp>

#include <abyss/views/Actors/Enemy/Slime/SlimeVM.hpp>

namespace
{
	class ViewBinder;
}
namespace abyss::Actor::Enemy::Slime
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
			m_state = this->find<StateCtrl>();
		}

		this->attach<DeadCallback>(this);
		this->attach<SenserCtrl>(this);

		this->attach<ViewCtrl<SlimeVM>>()
			->createBinder<ViewBinder>(this);
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
	using namespace abyss::Actor;
	using namespace abyss::Actor::Enemy::Slime;

	class ViewBinder : public ViewCtrl<SlimeVM>::IBinder
	{
		IActor* m_pActor = nullptr;
		Ref<Body> m_body;
		Ref<HP> m_hp;

		std::unique_ptr<SlimeVM> m_view;
	private:
		SlimeVM* bind() const final
		{
			return &m_view->setTime(m_pActor->getDrawTimeSec())
				.setForward(m_body->getForward())
				.setPos(m_body->getPos())
				.setVelocity(m_body->getVelocity())
				.setIsDamaging(m_hp->isInInvincibleTime())
				;
		}
		void setup() final
		{
			m_body = m_pActor->find<Body>();
			m_hp = m_pActor->find<HP>();
		}
	public:
		ViewBinder(IActor* pActor) :
			m_pActor(pActor),
			m_view(std::make_unique<SlimeVM>())
		{}
	};
}
#include "Builder.hpp"

#include <abyss/entities/Actors/Enemy/SlimeEntity.hpp>
#include <abyss/params/Actors/Enemy/Slime/Param.hpp>

#include <abyss/components/Actors/Commons/HP.hpp>
#include <abyss/components/Actors/Commons/OutRoomChecker.hpp>
#include <abyss/components/Actors/Commons/ViewCtrl.hpp>
#include <abyss/components/Actors/Enemy/CommonBuilder.hpp>
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
	void Builder::Build(IActor* pActor, const SlimeEntity& entity)
	{
		// 共通ビルド
		CommonBuilder::Build(pActor, BuildOption{}
			.setInitPos(entity.pos)
			.setForward(entity.forward)
			.setInitHp(Param::Base::Hp)
			.setIsEnableRoomHit(true, ColDirection(ColDirection::Horizon))
			.setAudioSettingGroupPath(U"Enemy/Slime/slime.aase")
			.setIsEnableDeadCallback(false)
			.setInitState<WalkState>()
		);

		// Body調整
		{
			pActor->find<Body>()->setMaxSpeedX(Param::Walk::MaxSpeedX);
		}
		// ルーム外死亡
		{
			pActor->attach<OutRoomChecker>(pActor);
		}
		// 死亡時コールバック
		{
			pActor->attach<DeadCallback>(pActor);
		}
		// センサー制御
		{
			pActor->attach<SenserCtrl>(pActor);
		}

		// 描画制御
		{
			pActor->attach<ViewCtrl<SlimeVM>>()
				->createBinder<ViewBinder>(pActor);
		}
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
		void onStart() final
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
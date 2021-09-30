#include "Builder.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/entities/Actor/Enemy/LaunSharkEntity.hpp>
#include <abyss/params/Actor/Enemy/LaunShark/Param.hpp>

#include <abyss/components/Actor/Common/DamageCtrl.hpp>
#include <abyss/components/Actor/Common/TimeCounter.hpp>
#include <abyss/components/Actor/Common/VModel.hpp>
#include <abyss/components/Actor/Enemy/CommonBuilder.hpp>
#include <abyss/components/Actor/Enemy/LaunShark/State/SwimState.hpp>

#include <abyss/views/Actor/Enemy/LaunShark/LaunSharkVM.hpp>

namespace
{
	class ViewBinder;
}
namespace abyss::Actor::Enemy::LaunShark
{
	void Builder::Build(ActorObj* pActor, const LaunSharkEntity& entity)
	{
		// 共通ビルド
		CommonBuilder::Build(pActor, BuildOption{}
			.setInitPos(entity.pos)
			.setForward(entity.forward)
			.setBodySize(Param::Base::Size)
			.setInitHp(Param::Base::Hp)
			.setIsEnableRoomHit(true, ColDirection(ColDirection::All))
			.setAudioSettingGroupPath(U"Enemy/LaunShark/laun_shark.aase")
			.setInitState<SwimState>()
			.setVModelBinder<ViewBinder>(pActor)
		);

		// Body調整
		{
			pActor->find<Body>()->noneResistanced();
		}
		// カウンター制御
		{
			pActor->attach<TimeCounter>();
		}
	}
}

namespace
{
	using namespace abyss;
	using namespace abyss::Actor;
	using namespace abyss::Actor::Enemy::LaunShark;

	class ViewBinder : public IVModelBinder<LaunSharkVM>
	{
		ActorObj* m_pActor = nullptr;
		Ref<Body> m_body;
		Ref<DamageCtrl> m_damage;
		Ref<MotionCtrl> m_motion;
		std::unique_ptr<LaunSharkVM> m_view;
	private:
		LaunSharkVM* bind() const final
		{
			return &m_view->setTime(m_pActor->getTimeSec())
				.setPos(m_body->getPos())
				.setForward(m_body->getForward())
				.setIsDamaging(m_damage->isInInvincibleTime())
				.setAnimeTime(m_motion->animeTime())
				.setMotion(m_motion->get<Motion>())
				;
		}
		void onStart() final
		{
			m_body = m_pActor->find<Body>();
			m_damage = m_pActor->find<DamageCtrl>();
			m_motion = m_pActor->find<MotionCtrl>();
		}
	public:
		ViewBinder(ActorObj* pActor) :
			m_pActor(pActor),
			m_view(std::make_unique<LaunSharkVM>())
		{}
	};
}
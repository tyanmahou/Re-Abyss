#include "Builder.hpp"
#include <abyss/modules/Actors/base/ActorObj.hpp>
#include <abyss/entities/Actors/Enemy/LaunSharkEntity.hpp>
#include <abyss/params/Actors/Enemy/LaunShark/Param.hpp>

#include <abyss/components/Actors/Commons/HP.hpp>
#include <abyss/components/Actors/Commons/TimeCounter.hpp>
#include <abyss/components/Actors/Enemy/CommonBuilder.hpp>
#include <abyss/components/Actors/Enemy/LaunShark/State/SwimState.hpp>

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
		);

		// Body調整
		{
			pActor->find<Body>()->noneResistanced();
		}
		// カウンター制御
		{
			pActor->attach<TimeCounter>();
		}
		// 描画制御
		{
			pActor->attach<ViewCtrl<LaunSharkVM>>()
				->createBinder<ViewBinder>(pActor);
		}
	}
}

namespace
{
	using namespace abyss;
	using namespace abyss::Actor;
	using namespace abyss::Actor::Enemy::LaunShark;

	class ViewBinder : public ViewCtrl<LaunSharkVM>::IBinder
	{
		ActorObj* m_pActor = nullptr;
		Ref<Body> m_body;
		Ref<HP> m_hp;
		std::unique_ptr<LaunSharkVM> m_view;
	private:
		LaunSharkVM* bind() const final
		{
			return &m_view->setTime(m_pActor->getDrawTimeSec())
				.setPos(m_body->getPos())
				.setForward(m_body->getForward())
				.setIsDamaging(m_hp->isInInvincibleTime());
		}
		void onStart() final
		{
			m_body = m_pActor->find<Body>();
			m_hp = m_pActor->find<HP>();
		}
	public:
		ViewBinder(ActorObj* pActor) :
			m_pActor(pActor),
			m_view(std::make_unique<LaunSharkVM>())
		{}
	};
}
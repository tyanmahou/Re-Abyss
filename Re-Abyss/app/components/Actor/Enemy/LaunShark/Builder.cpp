#include <abyss/components/Actor/Enemy/LaunShark/Builder.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/entities/Actor/Enemy/LaunSharkEntity.hpp>
#include <abyss/params/Actor/Enemy/LaunShark/Param.hpp>

#include <abyss/components/Actor/Common/ColorCtrl.hpp>
#include <abyss/components/Actor/Common/TimeCounter.hpp>
#include <abyss/components/Actor/Common/VModel.hpp>
#include <abyss/components/Actor/Enemy/BuilderFromEntity.hpp>
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
			.setAudioSettingGroupPath(U"Enemy/LaunShark/LaunShark.aase")
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
	private:
		LaunSharkVM* bind() const final
		{
			return &m_view->setTime(m_pActor->getTimeSec())
				.setPos(m_body->getPos())
				.setForward(m_body->getForward())
				.setAnimeTime(m_motion->animeTime())
				.setMotion(m_motion->get<Motion>())
				.setColorMul(m_colorCtrl->colorMul())
				;
		}
		void onStart() final
		{
			m_body = m_pActor->find<Body>();
			m_colorCtrl = m_pActor->find<ColorCtrl>();
			m_motion = m_pActor->find<MotionCtrl>();
		}
	public:
		ViewBinder(ActorObj* pActor) :
			m_pActor(pActor),
			m_view(std::make_unique<LaunSharkVM>())
		{}
	private:
		ActorObj* m_pActor = nullptr;
		Ref<Body> m_body;
		Ref<ColorCtrl> m_colorCtrl;
		Ref<MotionCtrl> m_motion;
		std::unique_ptr<LaunSharkVM> m_view;
	};
}

namespace abyss::Actor::Enemy
{
    template struct BuilderFromEntity<EnemyType::LaunShark>;
    template<>
    void BuilderFromEntity<EnemyType::LaunShark>::Build(ActorObj* pActor, const EnemyEntity& entity)
    {
        LaunShark::Builder::Build(pActor, static_cast<const LaunSharkEntity&>(entity));
    }
}

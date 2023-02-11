#include <abyss/components/Actor/Enemy/Slime/Builder.hpp>

#include <abyss/entities/Actor/Enemy/SlimeEntity.hpp>
#include <abyss/params/Actor/Enemy/Slime/Param.hpp>

#include <abyss/components/Actor/Common/ColorCtrl.hpp>
#include <abyss/components/Actor/Common/OutRoomChecker.hpp>
#include <abyss/components/Common/MotionCtrl.hpp>
#include <abyss/components/Actor/Common/VModel.hpp>
#include <abyss/components/Actor/Enemy/BuilderFromEntity.hpp>
#include <abyss/components/Actor/Enemy/CommonBuilder.hpp>
#include <abyss/components/Actor/Enemy/Slime/State/WalkState.hpp>

#include <abyss/views/Actor/Enemy/Slime/SlimeVM.hpp>

namespace
{
	class Presenter;
}
namespace abyss::Actor::Enemy::Slime
{
	void Builder::Build(ActorObj* pActor, const SlimeEntity& entity)
	{
		// 共通ビルド
		CommonBuilder::Build(pActor, BuildOption{}
			.setInitPos(entity.pos)
			.setForward(entity.forward)
			.setInitHp(Param::Base::Hp)
			.setIsEnableRoomHit(true, ColDirection(ColDirection::Horizon))
			.setAudioSettingGroupPath(U"Enemy/Slime/Slime.aase")
			.setInitState<WalkState>()
			.setVModelPresenter<Presenter>(pActor)
		);

		// Body調整
		{
			pActor->find<Body>()->setMaxSpeedX(Param::Walk::MaxSpeedX);
		}
		// ルーム外死亡
		{
			pActor->attach<OutRoomChecker>(pActor);
		}

		// 崖チェック
		{
			pActor->attach<CliffChecker>(pActor)
				->setFrontOffset(s3d::Vec2{ -15, 0 })
				;
		}
	}
}


namespace
{
	using namespace abyss;
	using namespace abyss::Actor;
	using namespace abyss::Actor::Enemy::Slime;

	class Presenter : public IVModelPresenter<SlimeVM>
	{
	private:
		SlimeVM* bind() const final
		{
			return &m_view->setTime(m_pActor->getTimeSec())
				.setForward(m_body->getForward())
				.setPos(m_body->getPos())
				.setVelocity(m_body->getVelocity())
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
		Presenter(ActorObj* pActor) :
			m_pActor(pActor),
			m_view(std::make_unique<SlimeVM>())
		{}
	private:
		ActorObj* m_pActor = nullptr;
		Ref<Body> m_body;
		Ref<ColorCtrl> m_colorCtrl;
		Ref<MotionCtrl> m_motion;
		std::unique_ptr<SlimeVM> m_view;
	};
}

namespace abyss::Actor::Enemy
{
    template struct BuilderFromEntity<EnemyType::Slime>;
    template<>
    void BuilderFromEntity<EnemyType::Slime>::Build(ActorObj* pActor, const EnemyEntity& entity)
    {
        Slime::Builder::Build(pActor, static_cast<const SlimeEntity&>(entity));
    }
}

#include <abyss/components/Actor/Enemy/KingDux/BabyDux/Builder.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>

#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/ColorCtrl.hpp>
#include <abyss/components/Actor/Enemy/CommonBuilder.hpp>
#include <abyss/components/Actor/Enemy/KingDux/BabyDux/Main.hpp>
#include <abyss/components/Actor/Enemy/KingDux/BabyDux/EyeCtrl.hpp>
#include <abyss/components/Actor/Enemy/KingDux/BabyDux/ParentObserver.hpp>
#include <abyss/components/Actor/Enemy/KingDux/BabyDux/State/AppearState.hpp>
#include <abyss/components/Actor/Enemy/KingDux/BabyDux/State/MoveState.hpp>
#include <abyss/params/Actor/Enemy/KingDux/BabyDuxParam.hpp>
#include <abyss/views/Actor/Enemy/KingDux/BabyDux/BabyDuxVM.hpp>

namespace
{
	class ViewBinder;
}

namespace abyss::Actor::Enemy::KingDux::BabyDux
{
    namespace
    {
        void BuildCommon(ActorObj* pActor, const Vec2& pos, Forward forward, std::shared_ptr<IState> initState)
        {
            // 共通ビルド
            CommonBuilder::Build(pActor, BuildOption{}
                .setInitPos(pos)
                .setBodySize(BabyDuxParam::Base::Size)
                .setBodyPivot(BabyDuxParam::Base::Pivot)
                .setForward(forward)
                .setInitHp(BabyDuxParam::Base::Hp)
                .setIsEnableMapCollider(false)
                .setIsEnableItemDrop(false)
                .setAudioSettingGroupPath(U"Enemy/KingDux/BabyDux.aase")
                .setInitState(initState)
                .setVModelBinder<ViewBinder>(pActor)
            );
            // Body調整
            {
                pActor->find<Body>()->noneResistanced();
            }
            // 目の制御
            {
                pActor->attach<EyeCtrl>(pActor);
            }
        }
    }
	void Builder::Build(ActorObj* pActor, ActorObj* parent, const BuildDesc& desc)
	{
        // 共通ビルド
        auto parentBody = parent->find<Body>();
		const s3d::Vec2& parentPos = parentBody->getPos();
        auto pos = parentPos + desc.posOffset;
        BuildCommon(pActor, pos, parentBody->getForward(), std::make_shared<AppearState>());

		// Main
		{
			pActor->attach<Main>(pActor, desc, parentPos);
		}
		// 親監視
		{
			pActor->attach<ParentObserver>(pActor, parent);
		}
	}
    void Builder::Build(ActorObj* pActor, const BabyDuxEntity& entity)
    {
        // 共通ビルド
        BuildCommon(pActor, entity.pos, entity.forward, std::make_shared<MoveState>());
    }
}

namespace
{
	using namespace abyss;
	using namespace abyss::Actor;
	using namespace abyss::Actor::Enemy::KingDux;
	using namespace abyss::Actor::Enemy::KingDux::BabyDux;

	class ViewBinder : public IVModelBinder<BabyDuxVM>
	{
	public:
		ViewBinder(ActorObj* pActor) :
			m_pActor(pActor),
			m_view(std::make_unique<BabyDuxVM>())
		{}
	private:
		BabyDuxVM* bind() const final
		{
			return &m_view->setTime(m_pActor->getTimeSec())
				.setPos(m_body->getPos())
                .setEyePos(m_eyeCtrl->getEyePosL(), m_eyeCtrl->getEyePosR())
                .setAnimTime(m_motion->animeTime())
                .setMotion(m_motion->get<Motion>())
                .setColorMul(m_colorCtrl->colorMul())
				;
		}
		void onStart() final
		{
			m_body = m_pActor->find<Body>();
            m_motion = m_pActor->find<MotionCtrl>();
			m_colorCtrl = m_pActor->find<ColorCtrl>();
            m_eyeCtrl = m_pActor->find<EyeCtrl>();
		}
	private:
		ActorObj* m_pActor = nullptr;
		Ref<Body> m_body;
		Ref<MotionCtrl> m_motion;
        Ref<ColorCtrl> m_colorCtrl;
        Ref<EyeCtrl> m_eyeCtrl;
		std::unique_ptr<BabyDuxVM> m_view;
	};
}

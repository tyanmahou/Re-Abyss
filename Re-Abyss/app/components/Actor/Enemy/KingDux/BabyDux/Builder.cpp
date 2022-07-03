#include <abyss/components/Actor/Enemy/KingDux/BabyDux/Builder.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>

#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/ColorCtrl.hpp>
#include <abyss/components/Actor/Enemy/CommonBuilder.hpp>
#include <abyss/components/Actor/Enemy/KingDux/BabyDux/Main.hpp>
#include <abyss/components/Actor/Enemy/KingDux/BabyDux/ParentObserver.hpp>
#include <abyss/components/Actor/Enemy/KingDux/BabyDux/State/AppearState.hpp>
#include <abyss/params/Actor/Enemy/KingDux/BabyDuxParam.hpp>
#include <abyss/views/Actor/Enemy/KingDux/BabyDux/BabyDuxVM.hpp>

namespace
{
	class ViewBinder;
}

namespace abyss::Actor::Enemy::KingDux::BabyDux
{
	void Builder::Build(ActorObj* pActor, ActorObj* parent, const BuildDesc& desc)
	{
        // 共通ビルド
        auto parentBody = parent->find<Body>();
		const s3d::Vec2& parentPos = parentBody->getPos();
        auto pos = parentPos + desc.posOffset;
        CommonBuilder::Build(pActor, BuildOption{}
            .setInitPos(pos)
            .setBodyPivot(BabyDuxParam::Base::Pivot)
            .setForward(parentBody->getForward())
            .setInitHp(BabyDuxParam::Base::Hp)
            //.setCollider<MainCollider>(pActor)
            .setIsEnableMapCollider(false)
            .setIsEnableItemDrop(false)
            .setAudioSettingGroupPath(U"Enemy/KingDux/BabyDux.aase")
            .setInitState<AppearState>()
            .setVModelBinder<ViewBinder>(pActor)
        );

		// Main
		{
			pActor->attach<Main>(pActor, desc, parentPos);
		}
        // Body調整
        {
            pActor->find<Body>()->noneResistanced();
        }
		// 親監視
		{
			pActor->attach<ParentObserver>(pActor, parent);
		}
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
		}
	private:
		ActorObj* m_pActor = nullptr;
		Ref<Body> m_body;
		Ref<MotionCtrl> m_motion;
        Ref<ColorCtrl> m_colorCtrl;
		std::unique_ptr<BabyDuxVM> m_view;
	};
}

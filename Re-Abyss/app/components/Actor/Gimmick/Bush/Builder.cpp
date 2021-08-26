#include "Builder.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Commons/CustomDraw.hpp>
#include <abyss/components/Actor/Commons/Locator.hpp>
#include <abyss/components/Actor/Commons/CollisionCtrl.hpp>
#include <abyss/components/Actor/Commons/Colliders/RectCollider.hpp>
#include <abyss/components/Actor/Gimmick/Bush/TimeScaleCtrl.hpp>

#include <abyss/params/Actor/Gimmick/Bush/Param.hpp>
#include <abyss/views/Actor/Gimmick/Bush/BushVM.hpp>
#include <Siv3D.hpp>
namespace
{
    class Drawer;
}
namespace abyss::Actor::Gimmick::Bush
{
    void Builder::Build(ActorObj* pActor, const BushEntity& entity)
    {
        pActor->setDestoryTiming(DestoryTiming::CheckIn);
        // 座標
        {
            pActor->attach<Locator>()
                ->setPos(entity.pos);
        }

		// 衝突
		{
			pActor->attach<CollisionCtrl>(pActor)
				->setLayer(LayerGroup::Gimmick)
				.setToLayer(LayerGroup::Player | LayerGroup::Enemy);

			pActor
				->attach<RectCollider>(pActor)
				->setSize(Param::ColliderSize)
				.setOffset(Param::ColliderOffset);
		}

		// タイムスケール制御
		{
			pActor->attach<TimeScaleCtrl>(pActor);
		}

        // 描画
        {
            pActor->attach<CustomDraw>()
                ->setDrawer<Drawer>(pActor, entity)
                .setLayer(DrawLayer::WorldFront);
        }
    }
}

namespace
{
	using namespace abyss;
	using namespace abyss::Actor;
	using namespace abyss::Actor::Gimmick;
	using namespace abyss::Actor::Gimmick::Bush;

	class Drawer : public CustomDraw::IImpl
	{
	public:
		Drawer(ActorObj* pActor, const BushEntity& entity) :
			m_pActor(pActor),
			m_view(std::make_unique<BushVM>())
		{
			m_view->setKind(entity.kind);
			m_timeOffset = s3d::Math::Fmod(-entity.pos.x / 40.0 / Param::TimeOffsetFactor, Param::AnimTimeSec) + Param::AnimTimeSec;
		}

		void onStart() override
		{
			m_locator = m_pActor->find<ILocator>();
		}
		void onDraw() const override
		{
			m_view
				->setPos(m_locator->getCenterPos())
				.setTime(m_pActor->getDrawTimeSec() + m_timeOffset)
				.draw();
		}
	private:
		ActorObj* m_pActor;

		Ref<ILocator> m_locator;
		double m_timeOffset = 0;
		std::unique_ptr<BushVM> m_view;
	};
}


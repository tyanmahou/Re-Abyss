#include "Builder.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Commons/VModel.hpp>
#include <abyss/components/Actor/Commons/Locator.hpp>
#include <abyss/components/Actor/Commons/CollisionCtrl.hpp>
#include <abyss/components/Actor/Commons/Colliders/RectCollider.hpp>
#include <abyss/components/Actor/Gimmick/Bush/ColReactor.hpp>

#include <abyss/params/Actor/Gimmick/Bush/Param.hpp>
#include <abyss/views/Actor/Gimmick/Bush/BushVM.hpp>
#include <Siv3D.hpp>
namespace
{
	class ViewBinder;
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

			// 衝突反応
			pActor->attach<ColReactor>(pActor);
		}

        // 描画
        {
			pActor->attach<VModel>()
				->setBinder<ViewBinder>(pActor, entity)
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

	class ViewBinder : public IVModelBinder<BushVM>
	{
	public:
		ViewBinder(ActorObj* pActor, const BushEntity& entity) :
			m_pActor(pActor),
			m_view(std::make_unique<BushVM>())
		{
			m_view->setKind(entity.kind);
			m_timeOffset = s3d::Math::Fmod(-entity.pos.x / 40.0 / Param::TimeOffsetFactor, Param::AnimTimeSec) + Param::AnimTimeSec;
		}

		void onStart() override
		{
			m_locator = m_pActor->find<ILocator>();
			m_colReactor = m_pActor->find<ColReactor>();
		}
		BushVM* bind() const override
		{
			return &m_view
				->setPos(m_locator->getCenterPos())
				.setTime(m_pActor->getDrawTimeSec() + m_timeOffset)
				.setResizeRate(m_colReactor->getResizeRate());
		}
	private:
		ActorObj* m_pActor;

		Ref<ILocator> m_locator;
		Ref<ColReactor> m_colReactor;
		double m_timeOffset = 0;
		std::unique_ptr<BushVM> m_view;
	};
}


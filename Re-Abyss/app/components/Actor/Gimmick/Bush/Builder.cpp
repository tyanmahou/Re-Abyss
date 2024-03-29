#include <abyss/components/Actor/Gimmick/Bush/Builder.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/VModel.hpp>
#include <abyss/components/Actor/Common/Locator.hpp>
#include <abyss/components/Actor/Common/ColCtrl.hpp>
#include <abyss/components/Actor/Common/Collider.hpp>
#include <abyss/components/Actor/Common/Col/Collider/RectCollider.hpp>
#include <abyss/components/Actor/Gimmick/BuilderFromEntity.hpp>
#include <abyss/components/Actor/Gimmick/Bush/ColReactor.hpp>

#include <abyss/params/Actor/Gimmick/Bush/Param.hpp>
#include <abyss/views/Actor/Gimmick/Bush/BushVM.hpp>
#include <Siv3D.hpp>
namespace
{
	class Presenter;
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
			auto collider = pActor->attach<Collider>();
			collider->add<Col::RectCollider>(pActor)
				->setSize(Param::ColliderSize)
				.setOffset(Param::ColliderOffset);

			pActor->attach<ColCtrl>(pActor)
				->addBranch()
				->addNode<Col::Node>(collider->main())
				.setLayer(ColSys::LayerGroup::Gimmick)
				.setToLayer(ColSys::LayerGroup::Player | ColSys::LayerGroup::Enemy)
				;

			// 衝突反応
			pActor->attach<ColReactor>(pActor);
		}

        // 描画
        {
			pActor->attach<VModel>()
				->setPresenter<Presenter>(pActor, entity)
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

	class Presenter : public IVModelPresenter<BushVM>
	{
	public:
		Presenter(ActorObj* pActor, const BushEntity& entity) :
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
				.setTime(m_pActor->getTimeSec() + m_timeOffset)
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

namespace abyss::Actor::Gimmick
{
    template struct BuilderFromEntity<GimmickType::Bush>;
    template<>
    void BuilderFromEntity<GimmickType::Bush>::Build(ActorObj* pActor, const GimmickEntity& entity)
    {
        Bush::Builder::Build(pActor, static_cast<const BushEntity&>(entity));
    }
}

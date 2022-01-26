#include <abyss/components/Actor/Gimmick/Door/Builder.hpp>

#include <abyss/components/Actor/Common/VModel.hpp>
#include <abyss/components/Actor/Common/Collider.hpp>

#include <abyss/components/Actor/Gimmick/Door/DoorProxy.hpp>
#include <abyss/components/Actor/Gimmick/Door/GimmickReactor.hpp>

#include <abyss/views/Actor/Gimmick/Door/DoorVM.hpp>

namespace
{
	class ViewBinder;
}

namespace abyss::Actor::Gimmick::Door
{
    void Builder::Build(ActorObj* pActor, const DoorModel& door, const RoomModel& nextRoom)
    {
		pActor->setDestoryTiming(DestoryTiming::CheckIn);

		// プロキシー
		auto proxy = pActor->attach<DoorProxy>(pActor, door, nextRoom);

		// コライダー
		{
			pActor->attach<Collider>()
				->add([proxy] {return proxy->getCollider(); });
		}

		// ギミック反応
		{
			pActor->attach<GimmickReactor>(pActor);
		}

		// 描画制御
		{
			pActor->attach<VModel>()
				->setBinder<ViewBinder>(pActor)
				.setLayer(DrawLayer::WorldBack);
		}
    }
}

namespace
{
	using namespace abyss;
	using namespace abyss::Actor;
	using namespace abyss::Actor::Gimmick::Door;

	class ViewBinder : public IVModelBinder<DoorVM>
	{
	public:
		ViewBinder(ActorObj* pActor) :
			m_pActor(pActor),
			m_view(std::make_unique<DoorVM>())
		{}

		void onStart() override
		{
			m_door = m_pActor->find<DoorProxy>();
		}
		DoorVM* bind() const override
		{
			return &m_view
				->setPos(m_door->getPos())
				.setKind(m_door->getKind())
				.setTime(m_pActor->getTimeSec());
		}
	private:
		ActorObj* m_pActor;
		Ref<DoorProxy> m_door;

		std::unique_ptr<DoorVM> m_view;
	};
}
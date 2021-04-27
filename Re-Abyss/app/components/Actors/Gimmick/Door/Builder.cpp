#include "Builder.hpp"

#include <abyss/components/Actors/Commons/CustomCollider.hpp>
#include <abyss/components/Actors/Commons/CustomDraw.hpp>
#include <abyss/components/Actors/Gimmick/Door/DoorProxy.hpp>
#include <abyss/components/Actors/Gimmick/Door/GimmickReacter.hpp>

#include <abyss/views/actors/Gimmick/Door/DoorVM.hpp>

namespace
{
	class Drawer;
}

namespace abyss::Actor::Gimmick::Door
{
    void Builder::Build(IActor* pActor, const DoorModel& door, const RoomModel& nextRoom)
    {
		pActor->setDestoryTiming(DestoryTiming::CheckIn);

		// プロキシー
		auto proxy = pActor->attach<DoorProxy>(pActor, door, nextRoom);

		// コライダー
		{
			pActor->attach<CustomCollider>()
				->setColFunc([proxy] {return proxy->getCollider(); });
		}

		// ギミック反応
		{
			pActor->attach<GimmickReacter>(pActor);
		}

		// 描画制御
		{
			pActor->attach<CustomDraw>()
				->setDrawer<Drawer>(pActor);
		}
    }
}

namespace
{
	using namespace abyss;
	using namespace abyss::Actor;
	using namespace abyss::Actor::Gimmick::Door;

	class Drawer : public CustomDraw::IImpl
	{
	public:
		Drawer(IActor* pActor) :
			m_pActor(pActor),
			m_view(std::make_unique<DoorVM>())
		{}

		void onStart() override
		{
			m_door = m_pActor->find<DoorProxy>();
		}
		void onDraw() const override
		{
			m_view
				->setPos(m_door->getPos())
				.setKind(m_door->getKind())
				.setTime(m_pActor->getDrawTimeSec())
				.draw();
		}
	private:
		IActor* m_pActor;
		Ref<DoorProxy> m_door;

		std::unique_ptr<DoorVM> m_view;
	};
}
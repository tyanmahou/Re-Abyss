#include "Builder.hpp"

#include <abyss/components/Actors/Commons/CustomCollider.hpp>
#include <abyss/components/Actors/Gimmick/Door/DoorProxy.hpp>
#include <abyss/components/Actors/Gimmick/Door/GimmickReacter.hpp>

namespace abyss::Actor::Gimmick::Door
{
    void Builder::Build(IActor* pActor, const DoorModel& door, const RoomModel& nextRoom)
    {
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
    }
}
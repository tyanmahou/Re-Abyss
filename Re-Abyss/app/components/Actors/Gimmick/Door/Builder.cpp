#include "Builder.hpp"

#include <abyss/components/Actors/Commons/CustomCollider.hpp>
#include <abyss/components/Actors/Commons/CollisionCtrl.hpp>
#include <abyss/components/Actors/Gimmick/Door/DoorProxy.hpp>
#include <abyss/models/Collision/LayerGroup.hpp>

namespace abyss::Actor::Gimmick::Door
{
    void Builder::Build(IActor* pActor, const DoorModel& door, const RoomModel& nextRoom)
    {
		pActor->setTag(Tag::Door{});

		// プロキシー
		auto proxy = pActor->attach<DoorProxy>(pActor, door, nextRoom);

		// 衝突
		{
			pActor->attach<CollisionCtrl>(pActor)
				->setLayer(LayerGroup::Gimmick);

			pActor->attach<CustomCollider>()
				->setColFunc([proxy] {return proxy->getCollider(); });
		}
    }
}
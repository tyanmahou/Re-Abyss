#include "DoorActor.hpp"
#include <abyss/models/Collision/LayerGroup.hpp>
#include <abyss/components/Actors/Commons/CustomCollider.hpp>
#include <abyss/components/Actors/Commons/CollisionCtrl.hpp>
#include <abyss/components/Actors/Gimmick/Door/DoorProxy.hpp>

#include <Siv3D.hpp>

namespace abyss::Actor::Gimmick::Door
{
	DoorActor::DoorActor(const DoorModel& door, const RoomModel& nextRoom)
	{
		m_tag = Tag::Door{};
		auto proxy = this->attach<DoorProxy>(this, door, nextRoom);
		this->attach<CollisionCtrl>(this)->setLayer(LayerGroup::Gimmick);
		auto col = this->attach<CustomCollider>();
		col->setColFunc([proxy] {return proxy->getCollider(); });
	}

}
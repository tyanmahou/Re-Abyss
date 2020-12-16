#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/models/Room/RoomModel.hpp>
#include <abyss/models/Actors/Gimmick/Door/DoorModel.hpp>

namespace abyss::Actor::Gimmick::Door
{
	class DoorActor : public IActor
	{

	public:
		DoorActor(const DoorModel& door, const RoomModel& nextRoom);
	};
}
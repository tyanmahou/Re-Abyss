#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>
#include <abyss/models/actors/Door/DoorActor.hpp>

namespace abyss
{
	class DoorTranslator
	{
	public:
		static std::shared_ptr<DoorActor> ToActorPtr(const DoorEntity& entity, const RoomModel& room);
	};
}

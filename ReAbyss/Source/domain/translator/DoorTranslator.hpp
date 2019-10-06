#pragma once
#include <memory>

namespace abyss
{
	class DoorActor;
	class RoomModel;
	struct DoorEntity;

	class DoorTranslator
	{
	public:
		std::shared_ptr<DoorActor> create(const DoorEntity& entity, const RoomModel& room) const;
	};
}

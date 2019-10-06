#pragma once
#include <memory>

namespace abyss
{
	class DoorModel;
	class RoomModel;
	struct DoorEntity;

	class DoorTranslator
	{
	public:
		std::shared_ptr<DoorModel> create(const DoorEntity& entity, const RoomModel& room) const;
	};
}

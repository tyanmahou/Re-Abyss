#include <domain/translator/DoorTranslator.hpp>
#include <domain/actor/DoorActor.hpp>
#include <data/entity/DoorEntity.hpp>

namespace abyss
{
	std::shared_ptr<DoorActor> DoorTranslator::create(const DoorEntity& entity, const RoomModel& room) const
	{
		return std::make_shared<DoorActor>(entity, room);
	}
}
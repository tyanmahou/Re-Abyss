#include <domain/translator/DoorTranslator.hpp>
#include <domain/model/object/DoorModel.hpp>
#include <data/entity/DoorEntity.hpp>

namespace abyss
{
	std::shared_ptr<DoorModel> DoorTranslator::create(const DoorEntity& entity, const RoomModel& room) const
	{
		return std::make_shared<DoorModel>(entity, room);
	}
}
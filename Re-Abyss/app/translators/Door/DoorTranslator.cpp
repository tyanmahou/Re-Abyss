#include "DoorTranslator.hpp"

namespace abyss
{
    std::shared_ptr<DoorActor> DoorTranslator::ToActorPtr(const DoorEntity& entity, const RoomModel& room)
    {
        return std::make_shared<DoorActor>(entity, room);
    }
}
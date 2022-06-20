#include <abyss/translators/Room/RoomTranslator.hpp>
#include <abyss/modules/Room/RoomData.hpp>
#include <abyss/entities/Room/RoomEntity.hpp>

namespace abyss
{
    Room::RoomData RoomTranslator::ToModel(const RoomEntity& entity)
    {
        return Room::RoomData(entity.region, entity.passbleBits, entity.lightColor);
    }
}

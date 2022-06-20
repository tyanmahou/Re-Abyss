#include <abyss/translators/Room/RoomTranslator.hpp>
#include <abyss/models/Room/RoomData.hpp>
#include <abyss/entities/Room/RoomEntity.hpp>

namespace abyss
{
    RoomData RoomTranslator::ToModel(const RoomEntity& entity)
    {
        return RoomData(entity.region, entity.passbleBits, entity.lightColor);
    }
}

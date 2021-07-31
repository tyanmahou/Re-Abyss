#include "RoomTranslator.hpp"
#include <abyss/models/Room/RoomModel.hpp>
#include <abyss/entities/Room/RoomEntity.hpp>

namespace abyss
{
    RoomModel RoomTranslator::ToModel(const RoomEntity& entity)
    {
        return RoomModel(entity.region, entity.passbleBits, entity.lightColor);
    }
}

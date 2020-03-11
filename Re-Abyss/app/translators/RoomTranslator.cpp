#include "RoomTranslator.hpp"
#include <abyss/models/RoomModel.hpp>
#include <abyss/entities/RoomEntity.hpp>

namespace abyss
{
    RoomModel RoomTranslator::ToModel(const RoomEntity& entity)
    {
        return RoomModel(entity.m_region, entity.m_passbleBits);
    }
}

#include "RoomTranslator.hpp"
#include <data/entity/RoomEntity.hpp>
#include <domain/model/RoomModel.hpp>

namespace abyss
{

	RoomModel RoomTranslator::create(const RoomEntity& entity) const
	{
		return RoomModel(entity.m_region, entity.m_passbleBits);
	}

}

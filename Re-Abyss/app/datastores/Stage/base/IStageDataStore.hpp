#pragma once

#include <Siv3D/Array.hpp>

#include <abyss/entities/Door/DoorEntity.hpp>
#include <abyss/entities/Map/MapEntity.hpp>
#include <abyss/entities/Room/RoomEntity.hpp>
#include <abyss/entities/Enemy/EnemyEntity.hpp>

namespace abyss
{
	class IStageDataStore
	{
	public:
		virtual ~IStageDataStore() = default;

		virtual s3d::Array<DoorEntity> getDoorEntity()const = 0;
		virtual s3d::Array<MapEntity> getMapEntity()const = 0;
		virtual s3d::Array<RoomEntity> getRoomEntity()const = 0;
		virtual s3d::Array<EnemyEntity> getEnemyEntity()const = 0;
	};
}
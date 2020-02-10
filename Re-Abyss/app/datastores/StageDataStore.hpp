#pragma once

#include <Siv3D/Fwd.hpp>
#include <Siv3D/Array.hpp>
#include <S3DTiled.hpp>

#include <abyss/entities/PlayerEntity.hpp>
#include <abyss/entities/DoorEntity.hpp>
#include <abyss/entities/MapEntity.hpp>
#include <abyss/entities/RoomEntity.hpp>
#include <abyss/entities/EnemyEntity.hpp>

namespace abyss
{
	class IStageDataStore
	{
	public:
		virtual s3d::Array<DoorEntity> getDoorEntity()const = 0;
		virtual s3d::Array<MapEntity> getMapEntity()const = 0;
		virtual s3d::Array<RoomEntity> getRoomEntity()const = 0;
		virtual s3d::Array<EnemyEntity> getEnemyEntity()const = 0;
	};

	class TiledStageDataStore : public IStageDataStore
	{
		s3dTiled::TiledMap m_tiledMap;
	public:
		TiledStageDataStore(const s3d::String& filePath);
		s3d::Array<DoorEntity> getDoorEntity()const override;
		s3d::Array<MapEntity> getMapEntity()const override;
		s3d::Array<RoomEntity> getRoomEntity()const override;
		s3d::Array<EnemyEntity> getEnemyEntity()const override;

		const s3dTiled::TiledMap& getTiledMap()const;
	};
}
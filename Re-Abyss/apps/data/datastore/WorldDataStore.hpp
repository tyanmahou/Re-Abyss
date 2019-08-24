#pragma once
#include "../entity/PlayerEntity.hpp"
#include "../entity/DoorEntity.hpp"
#include "../entity/MapEntity.hpp"
#include "../entity/RoomEntity.hpp"

#include<Siv3D/Array.hpp>
#include<S3DTiled.hpp>

namespace s3d
{
	class String;
}
namespace abyss
{
	struct DoorEntity;
	struct MapEntity;
	struct PlayerEntity;
	struct RoomEntity;

	class IWorldDataStore
	{
	public:
		virtual s3d::Array<DoorEntity> getDoorEntity()const = 0;
		virtual s3d::Array<MapEntity> getMapEntity()const = 0;
		virtual s3d::Array<RoomEntity> getRoomEntity()const = 0;
	};

	class TiledWorldDataStore : public IWorldDataStore
	{
		s3dTiled::TiledMap m_tiledMap;
	public:
		TiledWorldDataStore(const s3d::String& filePath);
		s3d::Array<DoorEntity> getDoorEntity()const override;
		s3d::Array<MapEntity> getMapEntity()const override;
		s3d::Array<RoomEntity> getRoomEntity()const override;
	};
}
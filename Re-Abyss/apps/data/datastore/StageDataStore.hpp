#pragma once
#include "../entity/PlayerEntity.hpp"
#include "../entity/DoorEntity.hpp"
#include "../entity/MapEntity.hpp"
#include "../entity/RoomEntity.hpp"
#include "../entity/EnemyEntity.hpp"

#include "../entity/BackGroundEntity.hpp"
#include "../entity/LayerViewEntity.hpp"

#include<Siv3D/Array.hpp>
#include<S3DTiled.hpp>

namespace s3d
{
	class String;
}
namespace abyss
{

	class IStageDataStore
	{
	public:
		virtual s3d::Array<DoorEntity> getDoorEntity()const = 0;
		virtual s3d::Array<MapEntity> getMapEntity()const = 0;
		virtual s3d::Array<RoomEntity> getRoomEntity()const = 0;
		virtual s3d::Array<EnemyEntity> getEnemyEntity()const = 0;

		virtual s3d::Array<BackGroundEntity> getBackGroundEntity()const = 0;
		virtual s3d::Array<LayerViewEntity> getLayerViewEntity() const = 0;
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

		s3d::Array<BackGroundEntity> getBackGroundEntity()const override;
		s3d::Array<LayerViewEntity> getLayerViewEntity() const override;
	};
}
﻿#pragma once

#include <Siv3D/Fwd.hpp>
#include <S3DTiled.hpp>
#include <abyss/datastores/Stage/base/IStageDataStore.hpp>

namespace abyss
{
	/// <summary>
	/// tmxからデータ取得
	/// </summary>
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
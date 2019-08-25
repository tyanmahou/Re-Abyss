#pragma once
#include <Siv3D/Array.hpp>
#include <data/datastore/StageDataStore.hpp>

namespace abyss
{
	class StageRepository
	{
		std::unique_ptr<IStageDataStore> m_dataStore;

		s3d::Array<RoomEntity> m_rooms;
		s3d::Array<MapEntity> m_maps;
		s3d::Array<DoorEntity> m_doors;

		s3d::Array<BackGroundEntity> m_bgs;
	public:
		StageRepository(const s3d::FilePath& path);

		const s3d::Array<RoomEntity>& getRooms() const;
		const s3d::Array<MapEntity>& getMaps() const;
		const s3d::Array<DoorEntity>& getDoors() const;

		const s3d::Array<BackGroundEntity>& getBgs() const;
	};
}
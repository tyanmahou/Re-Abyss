#pragma once
#include <Siv3D/Array.hpp>
#include <data/datastore/StageDataStore.hpp>

namespace abyss
{
	class StageUseCase;

	class StageRepository
	{
		s3d::Array<RoomEntity> m_rooms;
		s3d::Array<MapEntity> m_maps;
		s3d::Array<DoorEntity> m_doors;
		s3d::Array<EnemyEntity> m_enemies;
	public:
		StageRepository();

		std::unique_ptr<IStageDataStore> load(const s3d::FilePath& path);
		const s3d::Array<RoomEntity>& getRooms() const;
		const s3d::Array<MapEntity>& getMaps() const;
		const s3d::Array<DoorEntity>& getDoors() const;
		const s3d::Array<EnemyEntity>& getEnemies() const;
	};
}
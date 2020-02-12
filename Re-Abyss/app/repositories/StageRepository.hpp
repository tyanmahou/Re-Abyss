#pragma once
#include <Siv3D/Array.hpp>
#include <abyss/datastores/StageDataStore.hpp>

namespace abyss
{
	class IStageRepository
	{
	public:
		virtual const s3d::Array<RoomEntity>& getRooms() const = 0;
		virtual const s3d::Array<MapEntity>& getMaps() const = 0;
		virtual const s3d::Array<DoorEntity>& getDoors() const = 0;
		virtual const s3d::Array<EnemyEntity>& getEnemies() const = 0;
	};

	class StageRepository : public IStageRepository
	{
		s3d::Array<RoomEntity> m_rooms;
		s3d::Array<MapEntity> m_maps;
		s3d::Array<DoorEntity> m_doors;
		s3d::Array<EnemyEntity> m_enemies;
	public:
		StageRepository(const IStageDataStore& dataStore);

		const s3d::Array<RoomEntity>& getRooms() const;
		const s3d::Array<MapEntity>& getMaps() const;
		const s3d::Array<DoorEntity>& getDoors() const;
		const s3d::Array<EnemyEntity>& getEnemies() const;
	};
}
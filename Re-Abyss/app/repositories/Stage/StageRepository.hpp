#pragma once
#include <Siv3D/Array.hpp>
#include <abyss/datastores/Stage/base/IStageDataStore.hpp>
#include "base/IStageRepository.hpp"

namespace abyss
{
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
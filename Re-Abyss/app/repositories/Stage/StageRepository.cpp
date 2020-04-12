#include "StageRepository.hpp"

namespace abyss
{
	StageRepository::StageRepository(const IStageDataStore& dataStore):
		m_rooms(dataStore.getRoomEntity()),
		m_maps(dataStore.getMapEntity()),
		m_gimmicks(dataStore.getGimmickEntity()),
		m_enemies(dataStore.getEnemyEntity())
	{}

	const s3d::Array<RoomEntity>& StageRepository::getRooms() const
	{
		return m_rooms;
	}
	const s3d::Array<MapEntity>& StageRepository::getMaps() const
	{
		return m_maps;
	}
	const s3d::Array<std::shared_ptr<EnemyEntity>>& StageRepository::getEnemies() const
	{
		return m_enemies;
	}
	const s3d::Array<std::shared_ptr<GimmickEntity>>& StageRepository::getGimmicks() const
	{
		return m_gimmicks;
	}
}
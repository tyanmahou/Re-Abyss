#pragma once
#include <memory>
#include <abyss/services/Stage/base/IStageService.hpp>

namespace abyss
{
    class StageService : public IStageService
    {
		s3d::Array<RoomEntity> m_rooms;
		s3d::Array<std::shared_ptr<MapEntity>> m_maps;
		s3d::Array<std::shared_ptr<EnemyEntity>> m_enemies;
		s3d::Array<std::shared_ptr<GimmickEntity>> m_gimmicks;
	public:
		StageService(
			std::shared_ptr<IRoomDataStore> rooms,
			std::shared_ptr<IMapDataStore> maps,
			std::shared_ptr<IEnemyDataStore> enemies,
			std::shared_ptr<IGimmickDataStore> gimmicks
		);

		const s3d::Array<RoomEntity>& getRooms() const override { return m_rooms; }
		const s3d::Array<std::shared_ptr<MapEntity>>& getMaps() const { return m_maps; }
		const s3d::Array<std::shared_ptr<EnemyEntity>>& getEnemies() const { return m_enemies; }
		const s3d::Array<std::shared_ptr<GimmickEntity>>& getGimmicks() const { return m_gimmicks; }

    };
}
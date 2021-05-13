#pragma once
#include <memory>
#include <abyss/services/Stage/base/IStageService.hpp>
#include <Emaject.hpp>

namespace abyss
{
    class StageService : public IStageService
    {
		s3d::Array<RoomEntity> m_rooms;
		s3d::Array<std::shared_ptr<EnemyEntity>> m_enemies;
	public:
		INJECT_CTOR(StageService(
			std::shared_ptr<IRoomDataStore> rooms,
			std::shared_ptr<IEnemyDataStore> enemies
		));

		const s3d::Array<RoomEntity>& getRooms() const override { return m_rooms; }
		const s3d::Array<std::shared_ptr<EnemyEntity>>& getEnemies() const { return m_enemies; }
    };

	struct StageServiceInstaller : emaject::IInstaller
	{
		void onBinding(emaject::Container* container) const override;
	};
}
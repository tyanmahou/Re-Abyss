#pragma once
#include <Siv3D/Array.hpp>
#include <abyss/datastores/Stage/base/IStageDataStore.hpp>

namespace abyss
{
	class IStageRepository
	{
	public:
		virtual ~IStageRepository() = default;
		virtual const s3d::Array<RoomEntity>& getRooms() const = 0;
		virtual const s3d::Array<MapEntity>& getMaps() const = 0;
		virtual const s3d::Array<DoorEntity>& getDoors() const = 0;
		virtual const s3d::Array<std::shared_ptr<EnemyEntity>>& getEnemies() const = 0;
	};
}

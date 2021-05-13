#pragma once
#include <Siv3D/Array.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
	class IStageService
	{
	public:
		virtual ~IStageService() = default;
		virtual const s3d::Array<RoomEntity>& getRooms() const = 0;
		virtual const s3d::Array<std::shared_ptr<EnemyEntity>>& getEnemies() const = 0;
	};
}

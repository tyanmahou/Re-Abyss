#pragma once

#include <memory>
#include <Siv3D/Optional.hpp>
#include <Siv3D/Vector2D.hpp>

#include <abyss/commons/Fwd.hpp>
#include <abyss/models/RoomModel.hpp>
namespace abyss
{
    class StageModel
    {
    private:
		std::unique_ptr<IStageRepository> m_stageData;

	public:
		StageModel(std::unique_ptr<IStageRepository>&& repository) noexcept;

		s3d::Optional<RoomModel> findRoom(const s3d::Vec2& pos);
		bool init(WorldModel& world, const RoomModel& nextRoom);
		bool initRoom(WorldModel& world, const RoomModel& nextRoom);
    };
}
#pragma once

#include <memory>
#include <Siv3D/Optional.hpp>
#include <Siv3D/Vector2D.hpp>

#include <abyss/commons/Fwd.hpp>
#include <abyss/models/Room/RoomModel.hpp>
namespace abyss
{
    class Stage
    {
    private:
		std::unique_ptr<IStageRepository> m_stageData;
		std::unique_ptr<IStageView> m_view;

	public:
		Stage(std::unique_ptr<IStageRepository>&& repository, std::unique_ptr<IStageView>&& view) noexcept;
		~Stage();
		s3d::Optional<RoomModel> findRoom(const s3d::Vec2& pos);
		bool init(World& world, const RoomModel& nextRoom);
		bool initRoom(World& world, const RoomModel& nextRoom);

		inline IStageView* const getView()const { return m_view.get(); }
    };
}
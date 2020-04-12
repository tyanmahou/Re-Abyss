#pragma once

#include <memory>
#include <Siv3D/Optional.hpp>
#include <Siv3D/Vector2D.hpp>

#include <abyss/commons/Fwd.hpp>
#include <abyss/models/Room/RoomModel.hpp>
#include <abyss/models/Actors/StartPos/StartPosListModel.hpp>

namespace abyss
{
    class Stage
    {
    private:
		std::unique_ptr<IStageRepository> m_stageData;
		std::unique_ptr<IStageView> m_view;

		StartPosListModel m_startPos;
	public:
		Stage(std::unique_ptr<IStageRepository>&& repository, std::unique_ptr<IStageView>&& view) noexcept;
		~Stage();
		s3d::Optional<RoomModel> findRoom(const s3d::Vec2& pos) const;
		s3d::Optional<RoomModel> init(World& world);
		bool initRoom(World& world, const RoomModel& nextRoom);

		s3d::Optional<StartPosModel> findStartPos(const s3d::int32 startId) const;

		inline IStageView* const getView()const { return m_view.get(); }
    };
}
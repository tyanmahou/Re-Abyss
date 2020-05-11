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
		std::shared_ptr<IStageService> m_stageData;
		std::shared_ptr<IStageView> m_view;

		std::shared_ptr<Decor> m_decor;
		std::shared_ptr<BackGround> m_backGround;

		StartPosListModel m_startPos;
	public:
		Stage(
			std::shared_ptr<IStageService> service,
			std::shared_ptr<IStageView> view,
			std::shared_ptr<Decor> decor,
			std::shared_ptr<BackGround> backGround
		);
		~Stage();
		s3d::Optional<RoomModel> findRoom(const s3d::Vec2& pos) const;

		s3d::Optional<RoomModel> init(World& world, const std::shared_ptr<Player::PlayerActor>& player);
		s3d::Optional<RoomModel> init(World& world, s3d::int32 startId = 0);

		void initDecor(const Camera& camera) const;
		bool initRoom(World& world, const RoomModel& nextRoom);

		s3d::Optional<StartPosModel> findStartPos(const s3d::int32 startId) const;

		inline IStageView* const getView()const { return m_view.get(); }
    };
}
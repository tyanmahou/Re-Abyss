#pragma once

#include <memory>
#include <Siv3D/Optional.hpp>
#include <Siv3D/Vector2D.hpp>

#include <abyss/commons/Fwd.hpp>
#include <abyss/models/Room/RoomModel.hpp>
#include <abyss/models/Actors/Gimmick/StartPos/StartPosListModel.hpp>

namespace abyss
{
    class Stage
    {
    private:
		std::shared_ptr<StageData> m_stageData;

		StartPosListModel m_startPos;

		Manager* m_pManager;
	public:
		Stage();
		~Stage();
		s3d::Optional<RoomModel> findRoom(const s3d::Vec2& pos) const;

		void setup(Manager* pManager);

		void initBackGround(BackGround& backGround);
		void initDecorGraphics(Decor& decor);

		s3d::Optional<RoomModel> init(World& world, const std::shared_ptr<Player::PlayerActor>& player);
		s3d::Optional<RoomModel> init(World& world, s3d::int32 startId = 0);

		void initDecor(Decor& decor, const Camera& camera) const;
		bool initRoom(World& world, const RoomModel& nextRoom);

		s3d::Optional<StartPosModel> findStartPos(const s3d::int32 startId) const;

		void load();
		void setStageData(std::shared_ptr<StageData> stageData);
    };
}
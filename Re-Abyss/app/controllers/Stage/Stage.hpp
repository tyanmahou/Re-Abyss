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
	private:

		bool initBackGround(BackGround& backGround) const;
		bool initDecorGraphics(Decor& decor) const;
		bool initDecor(Decor& decor, const Camera& camera) const;
		bool initRoom(World& world, const RoomModel& nextRoom) const;

	public:
		Stage();
		~Stage();

		void setManager(Manager* pManager);

		bool restart()const;
		bool init(const std::shared_ptr<Player::PlayerActor>& player) const;
		bool init(s3d::int32 startId = 0) const;

		bool checkOut() const;
		bool checkIn() const;

		s3d::Optional<StartPosModel> findStartPos(const s3d::int32 startId) const;
		s3d::Optional<RoomModel> findRoom(const s3d::Vec2& pos) const;

		void load();
		void setStageData(std::shared_ptr<StageData> stageData);
		std::shared_ptr<StageData> lockStageData()const;
    };
}
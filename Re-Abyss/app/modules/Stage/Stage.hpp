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
		enum class BuildTiming : s3d::int8
		{
			CheckIn = 0x01,
			CheckOut = 0x02,
			All = CheckIn | CheckOut,
		};
    private:
		std::shared_ptr<StageData> m_stageData;

		StartPosListModel m_startPos;

		Manager* m_pManager;
	private:

		bool initBackGround(BackGround& backGround) const;
		bool initDecor(Decors& decor, const RoomModel& nextRoom) const;
		bool initRoom(World& world, const RoomModel& nextRoom, BuildTiming buildTiming) const;

	public:
		Stage();
		~Stage();

		void setManager(Manager* pManager);

		bool restart()const;
		bool init(
			const std::shared_ptr<Actor::IActor>& player,
			const std::shared_ptr<Event::IEvent>& readyEvent
		) const;
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
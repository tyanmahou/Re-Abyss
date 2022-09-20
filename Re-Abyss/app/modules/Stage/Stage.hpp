#pragma once
#include <memory>
#include <Siv3D/Optional.hpp>
#include <Siv3D/Vector2D.hpp>

#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Room/RoomData.hpp>
#include <abyss/modules/Stage/StartPos/StartPosContainer.hpp>

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

        StartPosContainer m_startPos;

		Manager* m_pManager;
	private:

		bool initDecor(Decors& decor, const Room::RoomData& nextRoom) const;
		bool initWorld(World& world, const Room::RoomData& nextRoom, BuildTiming buildTiming) const;

	public:
		Stage();
		~Stage();

		void setManager(Manager* pManager);

		bool init() const;

		bool checkOut() const;
		bool checkIn() const;

        const s3d::String& mapName() const;

		s3d::Optional<StartPos> findStartPos(const s3d::int32 startId) const;
		s3d::Optional<Room::RoomData> findRoom(const s3d::Vec2& pos) const;

		void load();
		void setStageData(std::shared_ptr<StageData> stageData);
		std::shared_ptr<StageData> lockStageData()const;
    };
}

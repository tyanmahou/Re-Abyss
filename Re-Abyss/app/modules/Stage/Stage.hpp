#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Room/RoomData.hpp>
#include <abyss/modules/Stage/StartPos/StartPosContainer.hpp>
#include <Siv3D/Optional.hpp>
#include <Siv3D/Vector2D.hpp>
#include <Emaject.hpp>

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

    private:
        [[INJECT(setStageData)]]
        void setStageData(std::shared_ptr<StageData> stageData);

        bool initDecor(Decors& decor, const Room::RoomData& nextRoom) const;
        bool initActor(Actors& actors, const Room::RoomData& nextRoom, BuildTiming buildTiming) const;

    private:
        std::shared_ptr<StageData> m_stageData;

        StartPosContainer m_startPos;

        Manager* m_pManager;
    };
}

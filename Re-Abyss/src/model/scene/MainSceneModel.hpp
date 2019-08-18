#pragma once

#include "../GameCamera.hpp"
#include "../Room.hpp"
#include "../BgModel.hpp"
#include "../MapInfoModel.hpp"
#include "../DoorInfoModel.hpp"
#include "../objects/PlayerModel.hpp"
#include "../WorldModel.hpp"

namespace abyss
{
	struct Transformer2D;

	class MainSceneModel
	{
		WorldModel world;
		std::shared_ptr<PlayerModel> m_player;
		GameCamera m_camera;
		Array<Room> m_rooms;
		Array<BgModel> m_bgs;
		Array<MapInfoModel> m_mapInfos;
		Array<DoorInfoModel> m_doorInfos;

	public:
		MainSceneModel();

		void init();
		void update();

		const GameCamera& getCamera() const;

		void addRoom(const Room& room);
		void addBgModel(const BgModel& bg);
		const Array<BgModel>& getBgs() const;

		void addMapInfoModel(const MapInfoModel& info);
		void addDoorInfoModel(const DoorInfoModel& room);

		const WorldModel& getWorld() const;
	};
}
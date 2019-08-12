#pragma once

#include "../GameCamera.hpp"
#include "../Room.hpp"
#include "../BgModel.hpp"
#include "../objects/PlayerModel.hpp"
#include "../objects/FloorModel.hpp"
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

	public:
		MainSceneModel();

		void init();
		void update();

		const GameCamera& getCamera() const;

		void addRoom(const Room& room);
		void addBgModel(const BgModel& bg);
		const Array<BgModel>& getBgs() const;

		const WorldModel& getWorld() const;
	};
}
#include "MainSceneModel.hpp"

using namespace abyss;
namespace
{
	Optional<Room> GetNextRoom(const Vec2& pos, const Array<Room>& rooms)
	{
		for (const auto& room : rooms) {
			if (room.getRegion().intersects(pos)) {
				return room;
			}
		}
		return s3d::none;
	}
}
namespace abyss
{
	MainSceneModel::MainSceneModel() :
		m_player(std::make_shared<PlayerModel>())
	{
	}

	void MainSceneModel::init()
	{
		m_player->setPos({ 480, 720 });
		m_camera.setRoom(m_rooms[0]);
		m_camera.update(m_player->getPos());
		world.registerObject(m_player);
	}

	void MainSceneModel::update()
	{
		world.update();

		Vec2 pos = m_player->getPos();
		m_camera.update(pos);
		m_camera.adjustPos(pos);
		m_player->setPos(pos);

		if (!m_camera.isCameraWork() && !m_camera.carentRoom().getRegion().intersects(pos)) {
			if (auto && next = ::GetNextRoom(pos, m_rooms)) {
				m_camera.startCameraWork(*next).withPlayerPos(pos);
			}
		}
	}

	const GameCamera& MainSceneModel::getCamera() const
	{
		return m_camera;
	}


	void MainSceneModel::addRoom(const Room& room)
	{
		m_rooms.push_back(room);
	}
	void MainSceneModel::addBgModel(const BgModel& bg)
	{
		m_bgs.push_back(bg);
	}
	const Array<BgModel>& MainSceneModel::getBgs() const
	{
		return m_bgs;
	}
	const WorldModel& MainSceneModel::getWorld() const
	{
		return world;
	}
}
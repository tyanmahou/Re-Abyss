#include "MainSceneModel.hpp"
#include "../factory/MapFactory.hpp"
#include "../objects/DoorModel.hpp"

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
		m_player->setPos({ 480, 2000 });
		m_camera.setRoom(::GetNextRoom(m_player->getPos(), m_rooms).value());
		m_camera.update(m_player->getPos());
		world.registerObject(m_player);

		MapFactory factory;
		for (const auto& map : m_mapInfos) {
			if (auto obj = factory.create(map)) {
				world.registerObject(obj);
			}
		}
		for (const auto& door : m_doorInfos) {
			if (auto && nextRoom = ::GetNextRoom(door.targetPos, m_rooms)) {
				world.createObject<DoorModel>(door, *nextRoom);
			}
		}
	}

	void MainSceneModel::update()
	{
		if (!m_camera.isCameraWork()) {
			world.update();
		}

		Vec2 pos = m_player->getPos();
		m_camera.update(pos);
		m_camera.adjustPos(pos);
		m_player->setPos(pos);
		if (m_camera.isOutOfRoomDeath(pos)) {
			return;
		}
		if (!m_camera.isCameraWork() && !m_camera.carentRoom().getRegion().intersects(pos)) {
			if (auto && next = ::GetNextRoom(pos, m_rooms)) {
				m_camera.startCameraWork(*next, pos);
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
	void MainSceneModel::addMapInfoModel(const MapInfoModel& info)
	{
		m_mapInfos.push_back(info);
	}
	void MainSceneModel::addDoorInfoModel(const DoorInfoModel& info)
	{
		m_doorInfos.push_back(info);
	}
	const WorldModel& MainSceneModel::getWorld() const
	{
		return world;
	}
}
#include "RoomManager.hpp"
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/Camera/CameraFix/base/ICameraFix.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <Siv3D.hpp>

namespace abyss::Room
{
	class RoomManager::CameraFix final: public ICameraFix
	{
	public:
		CameraFix(RoomManager* pRoomManager):
			m_pRoomManager(pRoomManager)
		{}

		s3d::Vec2 apply(const s3d::Vec2& target) const override
		{
			// TODO 自動スクロール
			return m_pRoomManager->m_currentRoom.cameraBorderAdjusted(target);
		}

		CameraFixPriority priority() const override
		{
			return CameraFixPriority::Normal;
		}
	private:
		RoomManager* m_pRoomManager;
	};
	RoomManager::RoomManager():
		m_cameraFix(std::make_shared<CameraFix>(this))
	{}
	void RoomManager::init()
	{
		m_pManager->getModule<Camera>()->addCameraFix(m_cameraFix);
	}
	bool RoomManager::isOutOfRoomDeath(const s3d::Vec2& pos, double margin) const
    {
		// TODO 自動スクロール
		if (!m_currentRoom.passable(Forward::Down) && pos.y > m_currentRoom.borders().down + margin) {
			return true;
		}
		return false;
    }
	bool RoomManager::canNextRoom(const s3d::Vec2& pos) const
	{
		if (this->isInRoom(pos)) {
			return false;
		}
		if (this->isOutOfRoomDeath(pos)) {
			// 落下の場合は無視
			return false;
		}
		return true;
	}
	bool RoomManager::applyNextRoom()
	{
		if (m_nextRoom) {
			this->setRoom(*m_nextRoom);
			this->setNextRoom(s3d::none);
			return true;
		}
		return false;
	}
	s3d::Vec2 RoomManager::fixPos(const s3d::Vec2& pos) const
	{
		// TODO 自動スクロール中はカメラのスクリーン内に入るように

		return m_currentRoom.borderAdjusted(pos);
	}
	void RoomManager::drawDeathLine() const
	{
		constexpr ColorF colors[4] = { ColorF(0,0), ColorF(0,0) ,ColorF(0,1),ColorF(0,1) };

		if (!m_currentRoom.passable(Forward::Down)) {
			auto region = m_currentRoom.getRegion();
			RectF(region.x, region.y + region.size.y - 40, region.w, 40).draw(colors);
		}
		if (m_nextRoom && !m_nextRoom->passable(Forward::Down)) {
			auto region = m_nextRoom->getRegion();
			RectF(region.x, region.y + region.size.y - 40, region.w, 40).draw(colors);
		}
	}
	void RoomManager::addCallback(std::shared_ptr<IRoomMoveCallback> callback)
	{
		m_callbacks.push_back(callback);
	}
	void RoomManager::onCheckOut()
	{
		s3d::Erase_if(m_callbacks, [](const Ref<IRoomMoveCallback>& c) {
			if (c) {
				c->onCheckOut();
				return false;
			}
			return true;
		});
	}
	void RoomManager::onCheckIn()
	{
		s3d::Erase_if(m_callbacks, [](const Ref<IRoomMoveCallback>& c) {
			if (c) {
				c->onCheckIn();
				return false;
			}
			return true;
		});
	}
}

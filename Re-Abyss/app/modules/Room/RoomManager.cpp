#include "RoomManager.hpp"
#include <Siv3D.hpp>

namespace abyss::Room
{
	RoomManager::RoomManager()
	{}
	bool RoomManager::isOutOfRoomDeath(const s3d::Vec2& pos, double margin) const
    {
		// @todo 自動スクロール
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
		// todo 自動スクロール中はカメラのスクリーン内に入るように

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
}

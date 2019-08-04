#include "Room.hpp"
#include "../common/Constants.hpp"
#include <S3DTiled.hpp>

using namespace s3dTiled;
using namespace s3d;

namespace abyss
{
	Room::Room(const TiledObject& obj):
		m_region(obj.toRectF()),
		m_passbleBits(0)
	{
		if (obj.getProperty(L"up").value_or(false)) {
			m_passbleBits |= static_cast<uint8>(Forward::Up);
		}
		if (obj.getProperty(L"down").value_or(false)) {
			m_passbleBits |= static_cast<uint8>(Forward::Down);
		}	
		if (obj.getProperty(L"left").value_or(false)) {
			m_passbleBits |= static_cast<uint8>(Forward::Left);
		}	
		if (obj.getProperty(L"right").value_or(false)) {
			m_passbleBits |= static_cast<uint8>(Forward::Right);
		}
	}

	bool Room::passable(Forward f) const
	{
		return (m_passbleBits & static_cast<uint8>(f)) != 0;
	}

	double Room::pos(Forward f) const
	{
		switch (f)
		{
		case Forward::Up:return m_region.y;
		case Forward::Down:return m_region.y + m_region.h;
		case Forward::Left:return m_region.x;
		case Forward::Right:return m_region.x + m_region.w;

		default:

			break;
		}
		return 0.0;
	}
	const s3d::RectF& Room::getRegion() const
	{
		return m_region;
	}
	Room::operator s3d::RectF() const
	{
		return m_region;
	}
	RoomBorders Room::cameraBorders() const
	{
		constexpr auto screenHarf = Constants::GameScreenSize / 2;

		RoomBorders ret;
		ret.up = pos(Forward::Up) + screenHarf.y;
		ret.down = pos(Forward::Down) - screenHarf.y;
		ret.left = pos(Forward::Left) + screenHarf.x;
		ret.right = pos(Forward::Right) - screenHarf.x;
		return ret;
	}
	s3d::Vec2 Room::cameraBorderAdjusted(s3d::Vec2 pos) const
	{
		auto border = this->cameraBorders();
		//���[
		if (pos.x < border.left)
		{
			pos.x = border.left;
		}//�E�[
		else if (pos.x > border.right)
		{
			pos.x = border.right;
		}

		//��[
		if (pos.y < border.up)
		{
			pos.y = border.up;
		}//���[
		else if (pos.y > border.down)
		{
			pos.y = border.down;
		}
		return pos;
	}
	RoomBorders Room::borders() const
	{
		RoomBorders ret;
		ret.up = pos(Forward::Up);
		ret.down = pos(Forward::Down);
		ret.left = pos(Forward::Left);
		ret.right = pos(Forward::Right);
		return ret;
	}
	s3d::Vec2 Room::borderAdjusted(s3d::Vec2 pos) const
	{
		auto border = this->borders();
		//���[
		if (!this->passable(Forward::Left) && pos.x < border.left)
		{
			pos.x = border.left;
		}//�E�[
		else if (!this->passable(Forward::Right) && pos.x > border.right)
		{
			pos.x = border.right;
		}

		//��[
		if (!this->passable(Forward::Up) && pos.y < border.up)
		{
			pos.y = border.up;
		}
		//���[
		// ���͗����Ď��ʔ��肪����̂Œ����͂���Ȃ�
		return pos;
	}
}
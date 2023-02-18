#include <abyss/modules/Room/RoomData.hpp>

#include <abyss/commons/Constants.hpp>
#include <abyss/utils/Collision/ColDirection.hpp>

using namespace s3d;

namespace abyss::Room
{
	RoomData::RoomData(const s3d::RectF& region, s3d::uint8 passbleBits, const s3d::Optional<s3d::ColorF>& lightColor) :
		m_region(region),
		m_passbleBits(passbleBits),
		m_lightColor(lightColor)
	{}

	bool RoomData::passable(ColDirection f) const
	{
		return (m_passbleBits & static_cast<uint8>(f)) != 0;
	}

	double RoomData::pos(ColDirection f) const
	{
        if (f.isUp()) {
            return m_region.y;
        }
        if (f.isDown()) {
            return m_region.y + m_region.h;
        }
        if (f.isLeft()) {
            return m_region.x;
        }
        if (f.isRight()) {
            return m_region.x + m_region.w;
        }
		return 0.0;
	}
	const s3d::RectF& RoomData::getRegion() const
	{
		return m_region;
	}
	s3d::RectF RoomData::getRegion(double margin) const
	{
		return m_region.stretched(margin);
	}
	RoomData::operator s3d::RectF() const
	{
		return m_region;
	}
	RoomBorders RoomData::cameraBorders() const
	{
		constexpr auto screenHarf = Constants::GameScreenSize / 2;

		RoomBorders ret;
		ret.up = pos(ColDirection::Up) + screenHarf.y;
		ret.down = pos(ColDirection::Down) - screenHarf.y;
		ret.left = pos(ColDirection::Left) + screenHarf.x;
		ret.right = pos(ColDirection::Right) - screenHarf.x;
		return ret;
	}
	s3d::Vec2 RoomData::cameraBorderAdjusted(s3d::Vec2 pos) const
	{
		auto border = this->cameraBorders();
		if (pos.x < border.left) {
			//左端
			pos.x = border.left;
		} else if (pos.x > border.right) {
			//右端
			pos.x = border.right;
		}

		if (pos.y < border.up) {
			//上端
			pos.y = border.up;
		} else if (pos.y > border.down) {
			//下端
			pos.y = border.down;
		}
		return pos;
	}
	RoomBorders RoomData::borders() const
	{
		RoomBorders ret;
		ret.up = pos(ColDirection::Up);
		ret.down = pos(ColDirection::Down);
		ret.left = pos(ColDirection::Left);
		ret.right = pos(ColDirection::Right);
		return ret;
	}
	s3d::Vec2 RoomData::borderAdjusted(s3d::Vec2 pos) const
	{
		auto border = this->borders();
		constexpr double epsilon = 1.0;
		if (!this->passable(ColDirection::Left) && pos.x < border.left + epsilon) {
			//左端
			pos.x = border.left + epsilon;
		} else if (!this->passable(ColDirection::Right) && pos.x > border.right - epsilon) {
			//右端
			pos.x = border.right - epsilon;
		}

		if (!this->passable(ColDirection::Up) && pos.y < border.up + epsilon) {
			//上端
			pos.y = border.up + epsilon;
		}
		//下端
		// 下は落ちて死ぬ判定があるので調整はいらない
		return pos;
	}
    s3d::Vec2 RoomData::strictBorderAdjusted(s3d::Vec2 pos) const
    {
		auto border = this->borders();
		if (pos.x < border.left) {
			//左端
			pos.x = border.left;
		} else if (pos.x > border.right) {
			//右端
			pos.x = border.right;
		}

		if (pos.y < border.up) {
			//上端
			pos.y = border.up;
		} else if (pos.y > border.down) {
			//上端
			pos.y = border.down;
		}

		return pos;
    }
	s3d::Vec2 RoomData::strictBorderAdjusted(s3d::Vec2 pos, const s3d::Optional<ColDirection>& strict) const
	{
        auto col = strict.value_or(this->getCol());

        auto border = this->borders();
        if (col.isLeft() && pos.x < border.left) {
            //左端
            pos.x = border.left;
        } else if (col.isRight() && pos.x > border.right) {
            //右端
            pos.x = border.right;
        }

        if (col.isUp() && pos.y < border.up) {
            //上端
            pos.y = border.up;
        } else if (col.isDown() && pos.y > border.down) {
            //上端
            pos.y = border.down;
        }

        return pos;
	}
	ColDirection RoomData::getCol() const
	{
		ColDirection col = ColDirection::None;
		if (!this->passable(ColDirection::Up)) {
			col |= ColDirection::Down;
		}
		if (!this->passable(ColDirection::Left)) {
			col |= ColDirection::Right;
		}
		if (!this->passable(ColDirection::Right)) {
			col |= ColDirection::Left;
		}
		return col;
	}
	const s3d::Optional<s3d::ColorF>& RoomData::getLightColor() const
	{
		return m_lightColor;
	}
}

#pragma once

#include <Siv3D/RectF.hpp>
#include <Siv3D/Color.hpp>
#include <Siv3D/Optional.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Collision/ColDirection.hpp>

namespace abyss::Room
{
    /// <summary>
    /// 部屋の境界線
    /// </summary>
    struct RoomBorders
    {
        double up = 0, down = 0, left = 0, right = 0;
    };

    class RoomData
    {
    private:
		s3d::RectF m_region;
		s3d::uint8 m_passbleBits;
		s3d::Optional<s3d::ColorF> m_lightColor;
	public:
		RoomData() = default;
		RoomData(const s3d::RectF & region, s3d::uint8 passbleBits, const s3d::Optional<s3d::ColorF>& lightColor);

		bool passable(ColDirection f) const;
		double pos(ColDirection f) const;
		const s3d::RectF& getRegion()const;
		s3d::RectF getRegion(double margin)const;

		operator s3d::RectF() const;

		RoomBorders cameraBorders()const;
		s3d::Vec2 cameraBorderAdjusted(s3d::Vec2 pos)const;

		RoomBorders borders()const;
		s3d::Vec2 borderAdjusted(s3d::Vec2 pos) const;
		s3d::Vec2 strictBorderAdjusted(s3d::Vec2 pos) const;
        s3d::Vec2 strictBorderAdjusted(s3d::Vec2 pos, const s3d::Optional<ColDirection>& strict) const;

		ColDirection getCol() const;

		const s3d::Optional<s3d::ColorF>& getLightColor() const;
    };
}

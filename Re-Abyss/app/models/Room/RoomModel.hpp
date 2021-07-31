#pragma once

#include <Siv3D/Rectangle.hpp>
#include <Siv3D/Color.hpp>
#include <Siv3D/Optional.hpp>
#include <abyss/types/Forward.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
    /// <summary>
    /// 部屋の境界線
    /// </summary>
    struct RoomBorders
    {
        double up = 0, down = 0, left = 0, right = 0;
    };

    class RoomModel
    {
    private:
		s3d::RectF m_region;
		s3d::uint8 m_passbleBits;
		s3d::Optional<s3d::Color> m_lightColor;
	public:
		RoomModel() = default;
		RoomModel(const s3d::RectF & region, s3d::uint8 passbleBits, const s3d::Optional<s3d::Color>& lightColor);

		bool passable(Forward f) const;
		double pos(Forward f) const;
		const s3d::RectF& getRegion()const;
		s3d::RectF getRegion(double margin)const;

		operator s3d::RectF() const;

		RoomBorders cameraBorders()const;
		s3d::Vec2 cameraBorderAdjusted(s3d::Vec2 pos)const;

		RoomBorders borders()const;
		s3d::Vec2 borderAdjusted(s3d::Vec2 pos) const;
		s3d::Vec2 strictBorderAdjusted(s3d::Vec2 pos) const;

		ColDirection getCol() const;

		const s3d::Optional<s3d::Color>& getLightColor() const;
    };
}
#pragma once
#include <Siv3D/Fwd.hpp>
#include <tuple>
namespace abyss
{
	bool Intersects(const s3d::Shape& a, const s3d::Shape& b);

	struct CShape;

	bool Intersects(const CShape& a, const CShape& b);

	using ColDirection = s3d::uint8;
	namespace collision
	{
		constexpr ColDirection None = 0x00;
		constexpr ColDirection Up = 0x01;
		constexpr ColDirection Down = 0x02;
		constexpr ColDirection Left = 0x04;
		constexpr ColDirection Right = 0x08;
		constexpr ColDirection All = 0x0f;

		std::pair<s3d::Vec2, s3d::uint8> Collision(const s3d::RectF& rect, const s3d::Ellipse& ellipse, ColDirection col = All);
		std::pair<s3d::Vec2, s3d::uint8> Collision(const s3d::RectF& from, const s3d::RectF& come, ColDirection col = All);
	}
}
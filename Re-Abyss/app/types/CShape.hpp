#pragma once
#include <variant>

#include <Siv3D/Rectangle.hpp>
#include <Siv3D/Circle.hpp>
#include <Siv3D/Ellipse.hpp>
#include <Siv3D/Vector2D.hpp>



namespace abyss
{
	using ShapeVariant = std::variant<
		s3d::RectF,
		s3d::Circle,
		s3d::Ellipse,
		s3d::Vec2,
		s3d::None_t
	>;

	/// <summary>
	/// 当たり判定に使用する型
	/// </summary>
	struct CShape : ShapeVariant
	{
		using ShapeVariant::variant;
	};
}
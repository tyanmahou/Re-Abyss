#pragma once
#include <variant>

#include <Siv3D/Rectangle.hpp>
#include <Siv3D/Circle.hpp>
#include <Siv3D/Quad.hpp>
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Array.hpp>


namespace abyss
{
	struct CShape;

	using ShapeVariant = std::variant<
		s3d::RectF,
		s3d::Circle,
		s3d::Quad,
		s3d::Vec2,
		s3d::Line,
		s3d::Triangle,
		s3d::Array<CShape>,
		s3d::None_t
	>;

	/// <summary>
	/// 当たり判定に使用する型
	/// </summary>
	struct CShape : ShapeVariant
	{
		using ShapeVariant::variant;
		using ShapeVariant::operator=;
	};
}
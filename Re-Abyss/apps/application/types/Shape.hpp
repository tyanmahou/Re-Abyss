#pragma once
#include <Siv3D/Rectangle.hpp>
#include <Siv3D/Circle.hpp>
#include <Siv3D/Ellipse.hpp>
#include <Siv3D/Vector2D.hpp>

#include <variant>
namespace abyss
{
	using ShapeVariant = std::variant<
		s3d::RectF,
		s3d::Circle,
		s3d::Ellipse,
		s3d::Vec2
	>;

	struct Shape : ShapeVariant
	{
		using ShapeVariant::variant;
	};
}
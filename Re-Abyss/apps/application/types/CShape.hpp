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
	/// <summary>
	/// “–‚½‚è”»’è‚ÉŽg—p‚·‚éŒ^
	/// </summary>
	struct CShape : ShapeVariant
	{
		using ShapeVariant::variant;
	};
}
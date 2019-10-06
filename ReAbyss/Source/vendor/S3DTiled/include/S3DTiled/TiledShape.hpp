#pragma once

#include<variant>

#include <Siv3D/Rectangle.hpp>
#include <Siv3D/Ellipse.hpp>
#include <Siv3D/LineString.hpp>
#include <Siv3D/Polygon.hpp>

namespace s3dTiled
{
	using TiledShape = std::variant<s3d::RectF, s3d::Ellipse, s3d::Polygon, s3d::LineString>;
}
#include "Collision.hpp"
#include "../types/CShape.hpp"

#include <Siv3D.hpp>

namespace {

	template<class T, class U, class = void>
	struct has_intersects : std::false_type
	{};

	template<class T, class U>
	struct has_intersects<T, U, std::void_t<decltype(s3d::Geometry2D::Intersect(std::declval<T&>(), std::declval<U&>()))>> : std::true_type
	{};
	template<class T, class U>
	constexpr bool has_intersects_v = has_intersects<T, U>::value;

	template<class T, class U>
	auto FailSafeIntersects(const T& a, const U& b)->std::enable_if_t<has_intersects<T, U>::value, bool>
	{
		return s3d::Geometry2D::Intersect(a, b);
	}

	template<class T, class U>
	auto FailSafeIntersects(const T&, const U&)->std::enable_if_t<!has_intersects<T, U>::value, bool>
	{
		throw new std::exception("warning: intersects");
		//return false;
	}

	template<class T>
	bool IntersectsShape(const T& a, const s3d::Shape& b)
	{
		switch (b.type())
		{
		case s3d::Shape::Type::Point:       return FailSafeIntersects(a, b.storage.point);
		case s3d::Shape::Type::Vec2:        return FailSafeIntersects(a, b.storage.vec2);
		case s3d::Shape::Type::LineInt:     return FailSafeIntersects(a, b.storage.lineInt);
		case s3d::Shape::Type::Line:        return FailSafeIntersects(a, b.storage.line);
		case s3d::Shape::Type::Rect:        return FailSafeIntersects(a, b.storage.rect);
		case s3d::Shape::Type::RectF:       return FailSafeIntersects(a, b.storage.rectF);
		case s3d::Shape::Type::Circle:      return FailSafeIntersects(a, b.storage.circle);
		case s3d::Shape::Type::Ellipse:     return FailSafeIntersects(a, b.storage.ellipse);
		case s3d::Shape::Type::Triangle:    return FailSafeIntersects(a, b.storage.triangle);
		case s3d::Shape::Type::Quad:        return FailSafeIntersects(a, *b.storage.quad);
		case s3d::Shape::Type::RoundRect:   return FailSafeIntersects(a, b.storage.roundRect);
		case s3d::Shape::Type::LineString:  return FailSafeIntersects(a, *b.storage.lineString);
		case s3d::Shape::Type::Polygon:	   return FailSafeIntersects(a, *b.storage.polygon);
		case s3d::Shape::Type::MultiPolygon:return FailSafeIntersects(a, *b.storage.multiPolygon);
		default:
			break;
		}
		return false;
	}
}
namespace abyss
{
	bool Intersects(const s3d::Shape& a, const s3d::Shape& b)
	{
		switch (a.type())
		{
		case s3d::Shape::Type::Point:       return IntersectsShape(a.storage.point, b);
		case s3d::Shape::Type::Vec2:        return IntersectsShape(a.storage.vec2, b);
		case s3d::Shape::Type::LineInt:     return IntersectsShape(a.storage.lineInt, b);
		case s3d::Shape::Type::Line:        return IntersectsShape(a.storage.line, b);
		case s3d::Shape::Type::Rect:        return IntersectsShape(a.storage.rect, b);
		case s3d::Shape::Type::RectF:       return IntersectsShape(a.storage.rectF, b);
		case s3d::Shape::Type::Circle:      return IntersectsShape(a.storage.circle, b);
		case s3d::Shape::Type::Ellipse:     return IntersectsShape(a.storage.ellipse, b);
		case s3d::Shape::Type::Triangle:    return IntersectsShape(a.storage.triangle, b);
		case s3d::Shape::Type::Quad:        return IntersectsShape(*a.storage.quad, b);
		case s3d::Shape::Type::RoundRect:   return IntersectsShape(a.storage.roundRect, b);
		case s3d::Shape::Type::LineString:  return IntersectsShape(*a.storage.lineString, b);
		case s3d::Shape::Type::Polygon:     return IntersectsShape(*a.storage.polygon, b);
		case s3d::Shape::Type::MultiPolygon:return IntersectsShape(*a.storage.multiPolygon, b);
		default:
			break;
		}
		return false;
	}
	bool Intersects(const CShape& a, const CShape& b)
	{
		std::visit([](const auto& a, const auto& b) {
			if constexpr (has_intersects_v<decltype(a), decltype(b)>) {
				s3d::Geometry2D::Intersect(a, b);
			}
		}, a, b);
	}
	std::pair<s3d::Vec2, s3d::uint8> collision::Collision(const s3d::RectF& rect, const s3d::Ellipse& ellipse, s3d::uint8 col)
	{
		bool up = (col & Up) != 0;
		bool down = (col & Down) != 0;
		bool left = (col & Left) != 0;
		bool right = (col & Right) != 0;

		Vec2 retPos = ellipse.center;
		uint8 retCol = None;

		Vec2 pos = rect.center;
		Vec2 colSize = rect.size;

		double a = ellipse.a;
		double b = ellipse.b;

		// ブロックの上端
		if (up && retPos.y < pos.y - colSize.y / 2.0 + 10) {
			retCol = retCol | Up;

			if (retPos.x >= pos.x - colSize.x / 2.0 && retPos.x <= pos.x + colSize.x / 2.0) {
				retPos.y = pos.y - (b + colSize.y / 2.0);
			}
			else if (retPos.x < pos.x - colSize.x / 2.0) {
				const double tmpX = pos.x - colSize.x / 2.0 - retPos.x;
				const double tmpY = std::sqrt(std::pow(a, 2) - std::pow(tmpX, 2)) * b / a;
				retPos.y = pos.y - colSize.y / 2.0 - tmpY;
			}
			else {
				const double tmpX = pos.x + colSize.x / 2.0 - retPos.x;
				const double tmpY = std::sqrt(std::pow(a, 2) - std::pow(tmpX, 2)) * b / a;
				retPos.y = pos.y - colSize.y / 2.0 - tmpY;
			}
		}
		// ブロックの下端
		else if (down && retPos.y > pos.y + colSize.y / 2.0 - 10) {
			retCol = retCol | Down;

			if (retPos.x >= pos.x - colSize.x / 2.0 && retPos.x <= pos.x + colSize.x / 2.0) {
				retPos.y = pos.y + (b + colSize.y / 2.0);
			}
			else if (retPos.x < pos.x - colSize.x / 2.0) {
				const double tmpX = pos.x - colSize.x / 2.0 - retPos.x;
				const double tmpY = std::sqrt(std::pow(a, 2) - std::pow(tmpX, 2)) * b / a;
				retPos.y = pos.y + colSize.y / 2.0 + tmpY;

			}
			else {
				const double tmpX = pos.x + colSize.x / 2.0 - retPos.x;
				const double tmpY = std::sqrt(std::pow(a, 2) - std::pow(tmpX, 2)) * b / a;
				retPos.y = pos.y + colSize.y / 2.0 + tmpY;
			}
		}
		//ブロックの左端
		else if (left && retPos.x < pos.x - colSize.x / 2.0 + 10) {
			retCol = retCol | Left;

			if (retPos.y >= pos.y - colSize.y / 2.0 && retPos.y <= pos.y + colSize.y / 2.0)
			{
				retPos.x = pos.x - (a + colSize.x / 2.0);
			}
			else if (retPos.y < pos.y - colSize.y / 2.0) {
				const double tmpY = pos.y - colSize.y / 2.0 - retPos.y;
				const double tmpX = std::sqrt(std::pow(b, 2) - std::pow(tmpY, 2)) * a / b;
				retPos.x = pos.x - colSize.x / 2.0 - tmpX;
			}
			else {
				const double tmpY = pos.y + colSize.y / 2.0 - retPos.y;
				const double tmpX = std::sqrt(std::pow(b, 2) - std::pow(tmpY, 2)) * a / b;
				retPos.x = pos.x - colSize.x / 2.0 - tmpX;
			}
		}
		//ブロックの右端
		else if (right && retPos.x > pos.x + colSize.x / 2.0 - 10) {
			retCol = retCol | Right;

			if (retPos.y >= pos.y - colSize.y / 2.0 && retPos.y <= pos.y + colSize.y / 2.0) {
				retPos.x = pos.x + (a + colSize.x / 2.0);
			}
			else if (retPos.y < pos.y - colSize.y / 2.0) {
				const double tmpY = pos.y - colSize.y / 2.0 - retPos.y;
				const double tmpX = std::sqrt(std::pow(b, 2) - std::pow(tmpY, 2)) * a / b;
				retPos.x = pos.x + colSize.x / 2.0 + tmpX;
			}
			else {
				const double tmpY = pos.y + colSize.y / 2.0 - retPos.y;
				const double tmpX = std::sqrt(std::pow(b, 2) - std::pow(tmpY, 2)) * a / b;
				retPos.x = pos.x + colSize.x / 2.0 + tmpX;
			}
		}
		return { retPos, retCol };
	}
}

std::pair<s3d::Vec2, s3d::uint8> abyss::collision::Collision(const s3d::RectF& from, const s3d::RectF& come, ColDirection col)
{
	bool up = (col & Up) != 0;
	bool down = (col & Down) != 0;
	bool left = (col & Left) != 0;
	bool right = (col & Right) != 0;

	Vec2 comePos = come.center;
	Vec2 comeSize = come.size;
	uint8 retCol = None;

	Vec2 fromPos = from.center;
	Vec2 fromSize = from.size;


	// ブロックの上端
	if (up && comePos.y + comeSize.y / 2 - (fromPos.y - fromSize.y / 2) < 10) {
		retCol = retCol | Up;
		comePos.y = fromPos.y - (comeSize.y + fromSize.y) / 2;
	}
	// ブロックの下端
	else if (down && fromPos.y + fromSize.y / 2 - (comePos.y - comeSize.y / 2) < 10) {
		retCol = retCol | Down;
		comePos.y = fromPos.y + (comeSize.y + fromSize.y) / 2;
	}
	//ブロックの左端
	else if (left && comePos.x + comeSize.x / 2 - (fromPos.x - fromSize.x / 2) < 10) {
		retCol = retCol | Left;
		comePos.x = fromPos.x - (comeSize.x + fromSize.x) / 2;
	}
	//ブロックの右端
	else if (right && fromPos.x + fromSize.x / 2 - (comePos.x - comeSize.x / 2) < 10) {
		retCol = retCol | Right;
		comePos.x = fromPos.x + (comeSize.x + fromSize.x) / 2;
	}
	return { comePos, retCol };
}

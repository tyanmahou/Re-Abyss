#include "Collision.hpp"
#include "../types/CShape.hpp"

#include <Siv3D.hpp>

namespace {

	template<class T, class U>
	concept HasIntersects = requires(T & a, U& b)
	{
		s3d::Geometry2D::Intersect(a, b);
	};
}
namespace abyss
{
	bool Intersects(const CShape& a, const CShape& b)
	{
		return std::visit([](const auto& a, const auto& b) {
			if constexpr (HasIntersects<decltype(a), decltype(b)>) {
				return s3d::Geometry2D::Intersect(a, b);
			}
			else {
				return false;
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

		Vec2 pos = rect.center();
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

	Vec2 comePos = come.center();
	Vec2 comeSize = come.size;
	uint8 retCol = None;

	Vec2 fromPos = from.center();
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

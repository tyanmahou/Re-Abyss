#include "Collision.hpp"

#include <Siv3D.hpp>

#include <abyss/types/CShape.hpp>

namespace
{
    template<class T, class U>
    concept HasIntersects = requires(T & a, U & b)
    {
        { s3d::Geometry2D::Intersect(a, b) }->bool;
    };
}

namespace abyss
{
    bool Intersects(const CShape& a, const CShape& b)
    {
        return std::visit([]<class T, class U>([[maybe_unused]] const T & a, [[maybe_unused]] const U & b)
        {
            if constexpr (HasIntersects<T, U>) {
                return s3d::Geometry2D::Intersect(a, b);
            } else {
                return false;
            }
        }, a, b);
    }
}

namespace abyss::collision
{
	std::pair<s3d::Vec2, ColDirection> Collision(const s3d::RectF& from, const s3d::RectF& come, ColDirection col)
	{
		bool up = (col & ColDirection::Up);
		bool down = (col & ColDirection::Down);
		bool left = (col & ColDirection::Left);
		bool right = (col & ColDirection::Right);

		Vec2 comePos = come.center();
		Vec2 comeSize = come.size;
		uint8 retCol = ColDirection::None;

		Vec2 fromPos = from.center();
		Vec2 fromSize = from.size;


		if (up && comePos.y + comeSize.y / 2 - (fromPos.y - fromSize.y / 2) < 10) {
			// ブロックの上端
			retCol = retCol | ColDirection::Up;
			comePos.y = fromPos.y - (comeSize.y + fromSize.y) / 2;
		} else if (down && fromPos.y + fromSize.y / 2 - (comePos.y - comeSize.y / 2) < 10) {
			// ブロックの下端
			retCol = retCol | ColDirection::Down;
			comePos.y = fromPos.y + (comeSize.y + fromSize.y) / 2;
		} else if (left && comePos.x + comeSize.x / 2 - (fromPos.x - fromSize.x / 2) < 10) {
			//ブロックの左端
			retCol = retCol | ColDirection::Left;
			comePos.x = fromPos.x - (comeSize.x + fromSize.x) / 2;
		} else if (right && fromPos.x + fromSize.x / 2 - (comePos.x - comeSize.x / 2) < 10) {
			//ブロックの右端
			retCol = retCol | ColDirection::Right;
			comePos.x = fromPos.x + (comeSize.x + fromSize.x) / 2;
		}
		return { comePos, retCol };
	}
    std::pair<s3d::Vec2, ColDirection> CollisionByPrevPos(const s3d::RectF& from, const s3d::RectF& come, const s3d::Vec2& prevPos, ColDirection col)
    {
		Vec2 comePos = come.center();
		Vec2 comeSize = come.size;
		uint8 retCol = ColDirection::None;

		Vec2 fromPos = from.center();
		Vec2 fromSize = from.size;
		Vec2 moveVec = fromPos - prevPos;

		bool up = (col & ColDirection::Up) && moveVec.y >= 0;
		bool down = (col & ColDirection::Down) && moveVec.y < 0;
		bool left = (col & ColDirection::Left) && moveVec.x >= 0;
		bool right = (col & ColDirection::Right) && moveVec.x < 0;

		auto comeMoveing = Line(prevPos, fromPos);
		if (up && from.top().intersects(comeMoveing)) {
			// ブロックの上端
			retCol = retCol | ColDirection::Up;
			comePos.y = fromPos.y - (comeSize.y + fromSize.y) / 2;
		} else if (down && from.bottom().intersects(comeMoveing)) {
			// ブロックの下端
			retCol = retCol | ColDirection::Down;
			comePos.y = fromPos.y + (comeSize.y + fromSize.y) / 2;
		} else if (left && from.left().intersects(comeMoveing)) {
			//ブロックの左端
			retCol = retCol | ColDirection::Left;
			comePos.x = fromPos.x - (comeSize.x + fromSize.x) / 2;
		} else if (right && from.right().intersects(comeMoveing)) {
			//ブロックの右端
			retCol = retCol | ColDirection::Right;
			comePos.x = fromPos.x + (comeSize.x + fromSize.x) / 2;
		}

		return { comePos, retCol };
    }
}
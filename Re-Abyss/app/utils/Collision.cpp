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


		// ブロックの上端
		if (up && comePos.y + comeSize.y / 2 - (fromPos.y - fromSize.y / 2) < 10) {
			retCol = retCol | ColDirection::Up;
			comePos.y = fromPos.y - (comeSize.y + fromSize.y) / 2;
		}
		// ブロックの下端
		else if (down && fromPos.y + fromSize.y / 2 - (comePos.y - comeSize.y / 2) < 10) {
			retCol = retCol | ColDirection::Down;
			comePos.y = fromPos.y + (comeSize.y + fromSize.y) / 2;
		}
		//ブロックの左端
		else if (left && comePos.x + comeSize.x / 2 - (fromPos.x - fromSize.x / 2) < 10) {
			retCol = retCol | ColDirection::Left;
			comePos.x = fromPos.x - (comeSize.x + fromSize.x) / 2;
		}
		//ブロックの右端
		else if (right && fromPos.x + fromSize.x / 2 - (comePos.x - comeSize.x / 2) < 10) {
			retCol = retCol | ColDirection::Right;
			comePos.x = fromPos.x + (comeSize.x + fromSize.x) / 2;
		}
		return { comePos, retCol };
	}
}
#pragma once

#include <tuple>
#include <Siv3D/Fwd.hpp>

#include <abyss/commons/Fwd.hpp>
#include <abyss/types/ColDirection.hpp>

namespace abyss
{
	[[nodiscard]] bool Intersects(const CShape& a, const CShape& b);

	namespace collision
	{
		std::pair<s3d::Vec2, ColDirection> Collision(const s3d::RectF& from, const s3d::RectF& come, ColDirection col);
		std::pair<s3d::Vec2, ColDirection> CollisionByPrevPos(const s3d::RectF& from, const s3d::RectF& come, const s3d::Vec2& prevPos, ColDirection col);
	}
}
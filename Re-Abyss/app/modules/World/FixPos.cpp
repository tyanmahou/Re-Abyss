#include "FixPos.hpp"
#include <Siv3D.hpp>

namespace
{
	// SivGeometry2D.cpp 移植

	bool IntersectLoose(const Triangle& a, const Triangle& b) noexcept
	{
		const int32 other[3] = { 1, 2, 0 };
		const int32 pindex[4] = { 1, 2, 0, 1 };
		const Triangle* tri[3] = { &a, &b, &a };

		for (int32 t = 0; t < 2; ++t) {
			const Triangle& ta = *tri[t];
			const Triangle& tb = *tri[t + 1];

			for (int32 i = 0; i < 3; ++i) {
				const Float2 vec = (ta.p(pindex[i + 1]) - ta.p(pindex[i])).normalized();
				const Float2 sepVec(vec.y, -vec.x);

				float s1min = sepVec.dot(ta.p(i));
				float s1max = sepVec.dot(ta.p(other[i]));

				if (s1min > s1max) {
					std::swap(s1min, s1max);
				}

				float s2min = sepVec.dot(tb.p(0));
				float s2max = sepVec.dot(tb.p(1));

				if (s2min > s2max) {
					std::swap(s2min, s2max);
				}

				const float d3 = sepVec.dot(tb.p(2));

				if (d3 < s2min) {
					s2min = d3;
				} else if (d3 > s2max) {
					s2max = d3;
				}

				if ((s2min < s1min && s1min < s2max)
					|| (s2min < s1max && s1max < s2max)
					|| (s1min < s2min && s2min < s1max)
					|| (s1min < s2max && s2max < s1max)) {
					continue;
				}

				return false;
			}
		}

		return true;
	}
	bool IntersectLoose(const Rect& a, const Triangle& b) noexcept
	{
		return IntersectLoose(Triangle(a.tl(), a.tr(), a.bl()), b)
			|| IntersectLoose(Triangle(a.bl(), a.tr(), a.br()), b);
	}
	bool IntersectLoose(const Rect& a, const Quad& b) noexcept
	{
		return IntersectLoose(a, Triangle(b.p0, b.p1, b.p2))
			|| IntersectLoose(a, Triangle(b.p0, b.p2, b.p3));
	}

}
namespace abyss
{
    FixPos::Result FixPos::ByLatestPos(const s3d::RectF& from, const s3d::RectF& come, ColDirection col)
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

    FixPos::Result FixPos::ByPrevPos(const s3d::RectF& from, const s3d::RectF& come, const s3d::Vec2& prevPos, ColDirection col)
    {
		Vec2 comePos = come.center();
		Vec2 comeSize = come.size;
		Vec2 moveVec = comePos - prevPos;
		uint8 retCol = ColDirection::None;

		Vec2 fromPos = from.center();
		Vec2 fromSize = from.size;

		bool up = (col & ColDirection::Up) && moveVec.y >= 0;
		bool down = (col & ColDirection::Down) && moveVec.y < 0;
		bool left = (col & ColDirection::Left) && moveVec.x >= 0;
		bool right = (col & ColDirection::Right) && moveVec.x < 0;

		static auto toQuad = [](const Line& line, const Vec2& v) {
			return Quad(line.begin - v, line.end - v, line.end, line.begin);
		};

		const Vec2 qSize = {
			Min(10.0, from.size.x / 4.0),
			Min(10.0, from.size.y / 4.0)
		};

		const RectF topRect{ from.tl(), { from.w, qSize.y } };
		const RectF bottomRect{ from.bl() - Vec2{0, qSize.y}, { from.w, qSize.y } };
		const RectF leftRect{ from.tl(), { qSize.x, from.h} };
		const RectF rightRect{ from.tr() - Vec2{qSize.x, 0}, { qSize.x, from.h} };

		if (up && ::IntersectLoose(topRect, toQuad(come.bottom(), moveVec))) {
			// ブロックの上端
			retCol = retCol | ColDirection::Up;
			comePos.y = fromPos.y - (comeSize.y + fromSize.y) / 2;
		} else if (down && ::IntersectLoose(bottomRect, toQuad(come.top(), moveVec))) {
			// ブロックの下端
			retCol = retCol | ColDirection::Down;
			comePos.y = fromPos.y + (comeSize.y + fromSize.y) / 2;
		} else if (left && ::IntersectLoose(leftRect, toQuad(come.right(), moveVec))) {
			//ブロックの左端
			retCol = retCol | ColDirection::Left;
			comePos.x = fromPos.x - (comeSize.x + fromSize.x) / 2;
		} else if (right && ::IntersectLoose(rightRect, toQuad(come.left(), moveVec))) {
			//ブロックの右端
			retCol = retCol | ColDirection::Right;
			comePos.x = fromPos.x + (comeSize.x + fromSize.x) / 2;
		}

		return { comePos, retCol };
	}

	FixPos::Result FixPos::InnerByLatestPos(const s3d::RectF& from, const s3d::Vec2& come, ColDirection col)
	{
		Vec2 ret = come;
		uint8 retCol = ColDirection::None;

		bool up = (col & ColDirection::Up);
		bool down = (col & ColDirection::Down);
		bool left = (col & ColDirection::Left);
		bool right = (col & ColDirection::Right);

		auto borderUp = from.y;
		auto borderDown = from.y + from.h;
		auto borderLeft = from.x;
		auto borderRight = from.x + from.w;

		if (right && come.x < borderLeft) {
			//左端
			ret.x = borderLeft;
			retCol = retCol | ColDirection::Right;

		} else if (left && come.x > borderRight) {
			//右端
			ret.x = borderRight;
			retCol = retCol | ColDirection::Left;
		}

		if (down && come.y < borderUp) {
			//上端
			ret.y = borderUp;
			retCol = retCol | ColDirection::Down;

		} else if (up && come.y > borderDown) {
			//上端
			ret.y = borderDown;
			retCol = retCol | ColDirection::Up;
		}

		return { ret , retCol };
	}
}

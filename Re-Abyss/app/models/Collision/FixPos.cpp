#include "FixPos.hpp"
#include <Siv3D.hpp>

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

		const Vec2 qSize = from.size / 4.0;

		const RectF topRect{ from.tl(), { from.w, qSize.y } };
		const RectF bottomRect{ from.bl() - Vec2{0, qSize.y}, { from.w, qSize.y } };
		const RectF leftRect{ from.tl(), { qSize.x, from.h } };
		const RectF rightRect{ from.tr() - Vec2{qSize.x, 0}, { qSize.x, from.h } };

		if (up && topRect.intersects(toQuad(come.bottom(), moveVec))) {
			// ブロックの上端
			retCol = retCol | ColDirection::Up;
			comePos.y = fromPos.y - (comeSize.y + fromSize.y) / 2;
		} else if (down && bottomRect.intersects(toQuad(come.top(), moveVec))) {
			// ブロックの下端
			retCol = retCol | ColDirection::Down;
			comePos.y = fromPos.y + (comeSize.y + fromSize.y) / 2;
		} else if (left && leftRect.intersects(toQuad(come.right(), moveVec))) {
			//ブロックの左端
			retCol = retCol | ColDirection::Left;
			comePos.x = fromPos.x - (comeSize.x + fromSize.x) / 2;
		} else if (right && rightRect.intersects(toQuad(come.left(), moveVec))) {
			//ブロックの右端
			retCol = retCol | ColDirection::Right;
			comePos.x = fromPos.x + (comeSize.x + fromSize.x) / 2;
		}

		return { comePos, retCol };
	}

}

#include "SweepUtil.hpp"
#include <abyss/types/CShape.hpp>
#include <Siv3D.hpp>
namespace abyss
{
    CShape SweepUtil::Sweep(const s3d::RectF& rect, const s3d::Vec2& move)
    {
        bool isZeroMoveX = move.x == 0.0;
        bool isZeroMoveY = move.y == 0.0;

        auto movedRect = rect.movedBy(move);

        if (isZeroMoveX && isZeroMoveY) {
            // 移動無し
            return movedRect;
        } else if (move.x > 0 && isZeroMoveY) {
            // 右に移動
            return RectF(rect.tl(), rect.size + move);
        } else if (move.x < 0 && isZeroMoveY) {
            // 左に移動
            return RectF(movedRect.tl(), rect.size - move);
        } else if (isZeroMoveX && move.y > 0) {
            // 下に移動
            return RectF(rect.tl(), rect.size + move);
        } else if (isZeroMoveX && move.y < 0) {
            // 上に移動
            return RectF(movedRect.tl(), rect.size - move);
        } else if (move.x > 0 && move.y > 0) {
            // 右下に移動
            Array<CShape> ret;
            ret.emplace_back(s3d::Quad(rect.tl(), rect.tr(), movedRect.bl(), rect.bl()));
            ret.emplace_back(s3d::Quad(rect.tr(), movedRect.tr(), movedRect.br(), movedRect.bl()));
            return ret;
        } else if (move.x > 0 && move.y < 0) {
            // 右上に移動
            Array<CShape> ret;
            ret.emplace_back(s3d::Quad(rect.tl(), movedRect.tl(), rect.br(), rect.bl()));
            ret.emplace_back(s3d::Quad(movedRect.tl(), movedRect.tr(), movedRect.br(), rect.br()));
            return ret;
        } else if (move.x < 0 && move.y > 0) {
            // 左下に移動
            Array<CShape> ret;
            ret.emplace_back(s3d::Quad(rect.tl(), rect.tr(), rect.br(), movedRect.br()));
            ret.emplace_back(s3d::Quad(movedRect.tl(), rect.tl(), movedRect.br(), movedRect.bl()));
            return ret;
        } else if (move.x < 0 && move.y < 0) {
            // 左上に移動
            Array<CShape> ret;
            ret.emplace_back(s3d::Quad(movedRect.tr(), rect.tr(), rect.br(), rect.bl()));
            ret.emplace_back(s3d::Quad(movedRect.tl(), movedRect.tr(), rect.bl(), movedRect.bl()));
            return ret;
        }
        // ここにはこないはず
        return movedRect;
    }
    CShape SweepUtil::Sweep(const s3d::Vec2& pos, const s3d::Vec2& move)
    {
        return Line(pos, pos + move);
    }
}

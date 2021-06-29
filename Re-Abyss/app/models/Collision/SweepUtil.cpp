#include "SweepUtil.hpp"
#include <abyss/types/CShape.hpp>
#include <Siv3D.hpp>

namespace
{
    Vec2 InnerCenter(const Triangle& triangle)
    {
        const auto& [p0, p1, p2] = triangle;
        const double d0 = p1.distanceFrom(p2);
        const double d1 = p2.distanceFrom(p0);
        const double d2 = p0.distanceFrom(p1);
        return (d0 * p0 + d1 * p1 + d2 * p2) / (d0 + d1 + d2);
    }
}
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

    CShape SweepUtil::Sweep(const s3d::Triangle& triangle, const s3d::Vec2& move)
    {
        if (move.isZero()) {
            // 移動無し
            return triangle;
        }
        auto centroid = triangle.centroid(); // 三角形の中にある点をてきとーに一つ

        size_t frontEdgeIndex = 0; // 前方の辺インデックス
        size_t backEdgeIndex = 0; // 後方の辺インデックス
        size_t backEdgeCount = 0; // 後方の辺の数
        for (size_t posIndex = 0; posIndex < 3; ++posIndex) {

            const auto& begin = triangle.p(posIndex);
            const auto& end = triangle.p((posIndex + 1) % 3);
            auto toEnd = end - begin;

            auto vertical = toEnd.cross(centroid - begin) < 0 ? Vec2(-toEnd.y, toEnd.x) : Vec2(toEnd.y, -toEnd.x);
            if (vertical.dot(move) <= 0) {
                ++backEdgeCount;
                backEdgeIndex = posIndex;
            } else {
                frontEdgeIndex = posIndex;
            }
            if (posIndex == 1) {
                if (backEdgeCount == 2) {
                    // 既に後ろに2つあったなら残りは必ず前なので計算不要
                    frontEdgeIndex = 2;
                    break;
                } else if (backEdgeCount == 0) {
                    // 既に前に2つあったなら残りは必ず後ろなので計算不要
                    backEdgeIndex = 2;
                    backEdgeCount = 1;
                    break;
                }
            }
        }
        if (backEdgeCount == 1) {
            // 後ろの辺が一つなら、移動後の三角形と後ろの辺が描く四角形
            Array<CShape> ret;
            ret.emplace_back(triangle.movedBy(move));
            const auto& begin = triangle.p(backEdgeIndex);
            const auto& end = triangle.p((backEdgeIndex + 1) % 3);
            ret.emplace_back(Quad(begin, begin + move, end + move, end));
            return ret;
        } else if (backEdgeCount == 2) {
            // 後ろの辺が二つなら、移動前の三角形と前の辺が描く四角形
            Array<CShape> ret;
            ret.emplace_back(triangle);
            const auto& begin = triangle.p(frontEdgeIndex);
            const auto& end = triangle.p((frontEdgeIndex + 1) % 3);
            ret.emplace_back(Quad(begin, begin + move, end + move, end));
            return ret;
        }

        // ここにはこないはず
        return triangle.movedBy(move);
    }
}

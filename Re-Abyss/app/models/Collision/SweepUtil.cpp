#include "SweepUtil.hpp"
#include <abyss/types/CShape.hpp>
#include <Siv3D.hpp>
#include <abyss/utils/Math/Math.hpp>
#include <abyss/utils/Overloaded.hpp>

namespace
{
    using namespace abyss;

    template<class T>
    concept Sweepable = requires(CShape (*f)(const T&, const Vec2&) )
    {
        f = &SweepUtil::Sweep;
    };
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
    CShape SweepUtil::Sweep(const s3d::Circle& circle, const s3d::Vec2& move)
    {
        if (move.isZero()) {
            return circle;
        }
        auto vertiacal = Vec2(move.y, -move.x).normalized();

        Array<CShape> ret;
        ret.emplace_back(circle);
        ret.emplace_back(circle.movedBy(move));
        Vec2 p0 = circle.center + vertiacal * circle.r;
        Vec2 p1 = circle.center - vertiacal * circle.r;
        ret.emplace_back(Quad(p0, p0 + move, p1 + move, p1));
        return ret;
    }
    CShape SweepUtil::Sweep(const s3d::Quad& quad, const s3d::Vec2& move)
    {
        if (move.isZero()) {
            return quad;
        }

        constexpr std::array<std::array<size_t, 3>, 2> posIndexes{ {
            {0, 1, 3},
            {3, 1, 2}
        } };
        constexpr std::array<size_t, 4> centroidIndexes{ 0,1,1,0 };

        // 各三角形の中心点求める
        std::array<Vec2, 2> centroids{};
        for (size_t index = 0; index < 2; ++index) {
            const auto& triangle = posIndexes[index];
            centroids[index] = (quad.p(triangle[0]) + quad.p(triangle[1]) + quad.p(triangle[2])) / 3.0;
        }

        Array<CShape> ret;
        ret.emplace_back(quad);
        for (size_t posIndex = 0; posIndex < 4; ++posIndex) {
            const auto& begin = quad.p(posIndex);
            const auto& end = quad.p((posIndex + 1) % 4);
            auto toEnd = end - begin;
            const auto& centroid = centroids[centroidIndexes[posIndex]];
            auto vertical = toEnd.cross(centroid - begin) < 0 ? Vec2(-toEnd.y, toEnd.x) : Vec2(toEnd.y, -toEnd.x);
            if (vertical.dot(move) > 0) {
                ret.emplace_back(Quad(begin, begin + move, end + move, end));
            }
        }
        return ret;
    }
    CShape SweepUtil::Sweep(const s3d::Vec2& pos, const s3d::Vec2& move)
    {
        if (move.isZero()) {
            return pos;
        }
        return Line(pos, pos + move);
    }

    CShape SweepUtil::Sweep(const s3d::Line& line, const s3d::Vec2& move)
    {
        if (move.isZero()) {
            return line;
        }
        return Quad(line.begin, line.begin + move, line.end + move, line.end);
    }

    CShape SweepUtil::Sweep(const s3d::Triangle& triangle, const s3d::Vec2& move)
    {
        if (triangle.p0 == triangle.p1 && triangle.p1 == triangle.p2) {
            // 何故か点だった
            return Sweep(triangle.p0, move);
        } else if (Math::IsZeroLoose((triangle.p1 - triangle.p0).cross(triangle.p2 - triangle.p0))) {
            // 何故か線だった
            if ((triangle.p1 - triangle.p0).dot((triangle.p2 - triangle.p0)) <= 0) {
                return Sweep(Line(triangle.p1, triangle.p2), move);
            } else if ((triangle.p2 - triangle.p1).dot((triangle.p0 - triangle.p1)) <= 0) {
                return Sweep(Line(triangle.p2, triangle.p0), move);
            } else {
                return Sweep(Line(triangle.p0, triangle.p1), move);
            }
        }

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
    CShape SweepUtil::Sweep(const CShape& shape, const s3d::Vec2& move)
    {
        return std::visit(overloaded{
            [&move](const Sweepable auto& s)->CShape {
                return SweepUtil::Sweep(s, move);
            },
            [&move](const Array<CShape>& ar)->CShape {
                Array<CShape> ret;
                for (const auto& s : ar) {
                    ret.push_back(SweepUtil::Sweep(s, move));
                }
                return ret;
            },
            []([[maybe_unused]] const None_t&)->CShape {
                return s3d::none;
            }
         }, shape);
    }
}

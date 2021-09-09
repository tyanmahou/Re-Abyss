#pragma once
#include <Siv3D/Vector2D.hpp>

namespace abyss
{
    /// <summary>
    /// 直交する2軸
    /// </summary>
    struct Axis2
    {
    private:
        s3d::Vec2 m_right{1, 0};
        s3d::Vec2 m_down{0, 1};

        constexpr Axis2(const s3d::Vec2& right, const s3d::Vec2& down):
            m_right(right),
            m_down(down)
        {}
    public:
        constexpr Axis2() = default;

        static constexpr Axis2 FromRight(const s3d::Vec2& right)
        {
            return Axis2(right, s3d::Vec2{ -right.y, right.x });
        }

        static constexpr Axis2 FromDown(const s3d::Vec2& down)
        {
            return Axis2(s3d::Vec2{ down.y, -down.x }, down);
        }

        /// <summary>
        /// 軸rightを返す
        /// </summary>
        /// <returns></returns>
        const s3d::Vec2& right() const
        {
            return m_right;
        }

        /// <summary>
        /// 軸downを返す
        /// </summary>
        /// <returns></returns>
        const s3d::Vec2& down() const
        {
            return m_down;
        }

        /// <summary>
        /// 絶対座標を相対座標に変換する
        /// </summary>
        /// <param name="xy"></param>
        /// <returns></returns>
        s3d::Vec2 relative(const s3d::Vec2& global) const
        {
            return {
                global.dot(m_right),
                global.dot(m_down),
            };
        }

        /// <summary>
        /// 絶対座標から相対座標Xに変換する
        /// </summary>
        /// <param name="xy"></param>
        /// <returns></returns>
        double relativeX(const s3d::Vec2& global) const
        {
            return global.dot(m_right);
        }

        /// <summary>
        /// 絶対座標から相対座標Yに変換する
        /// </summary>
        /// <param name="xy"></param>
        /// <returns></returns>
        double relativeY(const s3d::Vec2& global) const
        {
            return global.dot(m_down);
        }

        /// <summary>
        /// 絶対座標をright軸に写像
        /// </summary>
        /// <param name="xy"></param>
        /// <returns></returns>
        s3d::Vec2 projectRight(const s3d::Vec2& global) const
        {
            return global.projection(m_right);
        }

        /// <summary>
        /// 相対座標Xからright軸に写像
        /// </summary>
        /// <param name="xy"></param>
        /// <returns></returns>
        s3d::Vec2 projectRight(double relativeX) const
        {
            return m_right * relativeX;
        }

        /// <summary>
        ///  絶対座標をdown軸に写像
        /// </summary>
        /// <param name="xy"></param>
        /// <returns></returns>
        s3d::Vec2 projectDown(const s3d::Vec2& global) const
        {
            return global.projection(m_down);
        }

        /// <summary>
        /// 相対座標Yからdown軸に写像
        /// </summary>
        /// <param name="xy"></param>
        /// <returns></returns>
        s3d::Vec2 projectDown(double relativeY) const
        {
            return m_down * relativeY;
        }

        /// <summary>
        /// 相対座標から絶対座標に変換する
        /// </summary>
        /// <param name="xy"></param>
        /// <returns></returns>
        s3d::Vec2 global(const s3d::Vec2& relative) const
        {
            return m_right * relative.x + m_down * relative.y;
        }

        s3d::Vec2 operator *(const s3d::Vec2& relative) const
        {
            return global(relative);
        }
    };

    /// <summary>
    /// 自由な2軸 (直交性や正規化は問わない)
    /// ベクトルxyを自由な軸a, 軸bに対してsa + tbに分解する
    /// </summary>
    class FreeAxix2
    {
    public:
        s3d::Vec2 a{ 1, 0 };
        s3d::Vec2 b{ 0, 1 };

    public:
        FreeAxix2() = default;

        /// <summary>
        /// 一つの軸と、その軸と直行する軸を生成
        /// </summary>
        /// <param name="a"></param>
        constexpr FreeAxix2(const s3d::Vec2 & a) :
            a(a),
            b(-a.y, a.x)
        {}

        /// <summary>
        /// 2つの軸を指定して生成
        /// </summary>
        /// <param name="a"></param>
        /// <param name="b"></param>
        constexpr FreeAxix2(const s3d::Vec2 & a, const s3d::Vec2 & b) :
            a(a),
            b(b)
        {}
        s3d::Vec2 st(const s3d::Vec2 & xy) const
        {
            auto cross = a.cross(b);
            assert(cross != 0);

            return {
                xy.cross(b) / cross,
                a.cross(xy) / cross,
            };
        }

        double s(const s3d::Vec2 & xy) const
        {
            auto cross = a.cross(b);
            assert(cross != 0);

            return xy.cross(b) / cross;
        }

        double t(const s3d::Vec2 & xy) const
        {
            auto cross = a.cross(b);
            assert(cross != 0);

            return a.cross(xy) / cross;
        }

        s3d::Vec2 sa(const s3d::Vec2 & xy) const
        {
            return a * s(xy);
        }

        s3d::Vec2 tb(const s3d::Vec2 & xy) const
        {
            return b * t(xy);
        }

        bool isParallel() const
        {
            return a.cross(b) != 0;
        }

        bool isOrthogonal() const
        {
            return a.dot(b) == 0;
        }

        explicit operator bool()const
        {
            return isOrthogonal();
        }
    };
}
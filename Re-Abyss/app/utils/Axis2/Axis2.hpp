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
        s3d::Vec2 m_a{1, 0};
        s3d::Vec2 m_b{0, 1};

    public:
        Axis2() = default;

        /// <summary>
        /// 一つの軸と、その軸と直行する軸を生成
        /// </summary>
        /// <param name="a">正規化済みベクトル</param>
        constexpr Axis2(const s3d::Vec2& a) :
            m_a(a),
            m_b(-a.y, a.x)
        {}

        /// <summary>
        /// 主軸aを返す
        /// </summary>
        /// <returns></returns>
        const s3d::Vec2& a() const
        {
            return m_a;
        }

        /// <summary>
        /// 軸bを返す
        /// </summary>
        /// <returns></returns>
        const s3d::Vec2& b() const
        {
            return m_b;
        }

        /// <summary>
        /// xy座標をst座標に変換する
        /// </summary>
        /// <param name="xy"></param>
        /// <returns></returns>
        s3d::Vec2 st(const s3d::Vec2& xy) const
        {
            return {
                xy.dot(m_a),
                xy.dot(m_b),
            };
        }

        /// <summary>
        /// xy座標からs座標に変換する
        /// </summary>
        /// <param name="xy"></param>
        /// <returns></returns>
        double s(const s3d::Vec2& xy) const
        {
            return xy.dot(m_a);
        }

        /// <summary>
        /// xy座標からt座標に変換する
        /// </summary>
        /// <param name="xy"></param>
        /// <returns></returns>
        double t(const s3d::Vec2& xy) const
        {
            return xy.dot(m_b);
        }

        /// <summary>
        /// xy座標からsaベクトルに変換する
        /// </summary>
        /// <param name="xy"></param>
        /// <returns></returns>
        s3d::Vec2 sa(const s3d::Vec2& xy) const
        {
            return xy.projection(m_a);
        }

        /// <summary>
        /// s座標からsaベクトルに変換する
        /// </summary>
        /// <param name="xy"></param>
        /// <returns></returns>
        s3d::Vec2 sa(double s) const
        {
            return m_a * s;
        }

        /// <summary>
        /// t座標からtbベクトルに変換する
        /// </summary>
        /// <param name="xy"></param>
        /// <returns></returns>
        s3d::Vec2 tb(double t) const
        {
            return m_b * t;
        }

        /// <summary>
        /// xy座標からtbベクトルに変換する
        /// </summary>
        /// <param name="xy"></param>
        /// <returns></returns>
        s3d::Vec2 tb(const s3d::Vec2& xy) const
        {
            return xy.projection(m_b);
        }

        /// <summary>
        /// st座標からxy座標に変換する
        /// </summary>
        /// <param name="xy"></param>
        /// <returns></returns>
        s3d::Vec2 xy(const s3d::Vec2& st) const
        {
            return m_a * st.x + m_b * st.y;
        }

        s3d::Vec2 operator *(const s3d::Vec2& st) const
        {
            return xy(st);
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
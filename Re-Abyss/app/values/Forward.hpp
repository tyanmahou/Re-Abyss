#pragma once
#include <Siv3D/Vector2D.hpp>

namespace abyss
{
    /// <summary>
    /// 方向クラス
    /// </summary>
    class Forward
    {
    public:
        constexpr static Forward None()
        {
            return Forward{};
        }
        constexpr static Forward Left()
        {
            return Forward{ -1, 0 };
        }
        constexpr static Forward Right()
        {
            return Forward{ 1, 0 };
        }
        constexpr static Forward Up()
        {
            return Forward{0, -1};
        }
        constexpr static Forward Down()
        {
            return Forward{ 0, 1 };
        }
    public:
        constexpr Forward() :
            m_value()
        {
        }
        constexpr bool isRight() const
        {
            return m_value.x > 0;
        }
        constexpr bool isLeft() const
        {
            return m_value.x < 0;
        }
        constexpr bool isUp() const
        {
            return m_value.y < 0;
        }
        constexpr bool isDown() const
        {
            return m_value.y > 0;
        }
        constexpr double signH() const
        {
            return s3d::Sign(m_value.x);
        }
        constexpr double signV() const
        {
            return s3d::Sign(m_value.y);
        }
        constexpr Forward mirrored() const
        {
            return Forward{ -m_value.x, m_value.y };
        }
        constexpr Forward flipped() const
        {
            return Forward{ m_value.x, -m_value.y };
        }
        constexpr s3d::Vec2 toVec2() const
        {
            return m_value;
        }
        friend constexpr bool operator == (const Forward& a, const Forward& b)
        {
            return a.m_value == b.m_value;
        }
    private:
        constexpr Forward(double x, double y) :
            m_value(x, y)
        {
        }
    private:
        s3d::Vec2 m_value;
    };
}

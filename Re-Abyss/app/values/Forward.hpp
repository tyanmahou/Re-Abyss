#pragma once
#include <Siv3D/Vector2D.hpp>

namespace abyss
{
    /// <summary>
    /// 前方クラス
    /// </summary>
    class Forward
    {
    public:
        /// <summary>
        /// 方向なし
        /// </summary>
        /// <returns></returns>
        constexpr static Forward None()
        {
            return Forward{};
        }

        /// <summary>
        /// 左方向
        /// </summary>
        /// <returns></returns>
        constexpr static Forward Left()
        {
            return Forward{ -1, 0 };
        }

        /// <summary>
        /// 右方向
        /// </summary>
        /// <returns></returns>
        constexpr static Forward Right()
        {
            return Forward{ 1, 0 };
        }

        /// <summary>
        /// 上方向
        /// </summary>
        /// <returns></returns>
        constexpr static Forward Up()
        {
            return Forward{0, -1};
        }

        /// <summary>
        /// 左方向
        /// </summary>
        /// <returns></returns>
        constexpr static Forward Down()
        {
            return Forward{ 0, 1 };
        }
    public:
        constexpr Forward() :
            m_value()
        {
        }
        constexpr Forward(double x, double y) :
            m_value(x, y)
        {
        }
        constexpr Forward(const s3d::Vec2 value) :
            m_value(value)
        {
        }
        constexpr bool isNone() const
        {
            return m_value == s3d::Vec2{0, 0};
        }
        constexpr bool isValid() const
        {
            return !this->isNone();
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

        /// <summary>
        /// 水平方向反転
        /// </summary>
        /// <returns></returns>
        constexpr Forward mirrored() const
        {
            return Forward{ -m_value.x, m_value.y };
        }

        /// <summary>
        /// 鉛直方向反転
        /// </summary>
        /// <returns></returns>
        constexpr Forward flipped() const
        {
            return Forward{ m_value.x, -m_value.y };
        }

        /// <summary>
        /// 反対方向
        /// </summary>
        /// <returns></returns>
        constexpr Forward reversed() const
        {
            return Forward{ -m_value.x, -m_value.y };
        }

        /// <summary>
        /// 水平方向成分のみにする
        /// </summary>
        /// <returns></returns>
        constexpr Forward horizonal() const
        {
            return Forward{ m_value.x, 0 };
        }

        /// <summary>
        /// 鉛直方向成分のみにする
        /// </summary>
        /// <returns></returns>
        constexpr Forward vertical() const
        {
            return Forward{ 0, m_value.y };
        }

        /// <summary>
        /// 同じ方向か
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        constexpr bool isSame(const Forward& other) const
        {
            return m_value.dot(other.m_value) > 0;
        }

        /// <summary>
        /// 向き合っているか
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        constexpr bool isOpposite(const Forward& other) const
        {
            return m_value.dot(other.m_value) < 0;
        }

        constexpr s3d::Vec2 toVec2() const
        {
            return s3d::Sign(m_value);
        }
        friend constexpr bool operator == (const Forward& a, const Forward& b)
        {
            return a.m_value == b.m_value;
        }
    private:
        s3d::Vec2 m_value;
    };

    using Look = Forward;
}

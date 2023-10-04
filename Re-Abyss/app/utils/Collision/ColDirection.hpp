#pragma once
#include <Siv3D/Fwd.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss
{
    /// <summary>
    /// 衝突判定
    /// </summary>
    class ColDirection
    {
    public:
        using value_type = s3d::uint8;
    private:
        value_type m_value = 0;
    public:
        constexpr ColDirection() = default;

        constexpr ColDirection(value_type value):
            m_value(value)
        {}
        constexpr ColDirection(const ColDirection& other) :
            m_value(other.m_value)
        {}

        [[nodiscard]] explicit constexpr operator value_type() const
        {
            return m_value;
        }
        [[nodiscard]] explicit constexpr operator s3d::uint32() const
        {
            return static_cast<uint32>(m_value);
        }
        ColDirection& operator =(const ColDirection& other)
        {
            m_value = other.m_value;
            return *this;
        }

        ColDirection& operator =(value_type value)
        {
            m_value = value;
            return *this;
        }

        [[nodiscard]] constexpr ColDirection operator | (const ColDirection& other)const
        {
            return { static_cast<value_type>(m_value | other.m_value)};
        }

        [[nodiscard]] constexpr ColDirection operator | (const value_type& value)const
        {
            return { static_cast<value_type>(m_value | value)};
        }

        [[nodiscard]] friend ColDirection operator | (const value_type& left, const ColDirection& right)
        {
            return { static_cast<value_type>(left | right.m_value) };
        }

        ColDirection& operator |= (const value_type& value)
        {
            m_value |= value;
            return *this;
        }

        ColDirection& operator |= (const ColDirection& other)
        {
            return *this |= other.m_value;
        }

        [[nodiscard]] constexpr ColDirection operator & (const ColDirection& other)const
        {
            return { static_cast<value_type>(m_value & other.m_value) };
        }

        [[nodiscard]] constexpr ColDirection operator & (const value_type& value)const
        {
            return { static_cast<value_type>(m_value & value) };
        }

        [[nodiscard]] friend ColDirection operator & (const value_type& left, const ColDirection& right)
        {
            return { static_cast<value_type>(left & right.m_value) };
        }

        ColDirection& operator &= (const value_type& value)
        {
            m_value &= value;
            return *this;
        }
        ColDirection& operator &= (const ColDirection& other)
        {
            return *this &= other.m_value;
        }
        [[nodiscard]] constexpr bool operator == (const ColDirection& other)const
        {
            return m_value == other.m_value;
        }

        [[nodiscard]] constexpr bool operator == (const value_type& value)const
        {
            return m_value == value;
        }

        [[nodiscard]] friend bool operator == (const value_type& left, const ColDirection& right)
        {
            return left == right.m_value;
        }

        [[nodiscard]] constexpr bool operator != (const ColDirection& other)const
        {
            return m_value != other.m_value;
        }

        [[nodiscard]] constexpr bool operator != (const value_type& value)const
        {
            return m_value != value;
        }

        [[nodiscard]] friend bool operator != (const value_type& left, const ColDirection& right)
        {
            return left != right.m_value;
        }

        [[nodiscard]] constexpr explicit operator bool() const
        {
            return m_value != 0;
        }

        [[nodiscard]] constexpr bool isNone() const
        {
            return m_value == 0;
        }
        [[nodiscard]] constexpr bool isAny() const
        {
            return m_value != 0;
        }
        [[nodiscard]] constexpr bool isUp() const
        {
            return static_cast<bool>(*this & Up);
        }

        [[nodiscard]] constexpr bool isDown() const
        {
            return static_cast<bool>(*this & Down);
        }

        [[nodiscard]] constexpr bool isLeft() const
        {
            return static_cast<bool>(*this & Left);
        }

        [[nodiscard]] constexpr bool isRight() const
        {
            return static_cast<bool>(*this & Right);
        }

        /// <summary>
        /// 指定方向のあたり判定を無視する
        /// </summary>
        /// <param name="value"></param>
        /// <returns></returns>
        ColDirection& ignore(const value_type& value)
        {
            m_value &= static_cast<value_type>(~value);
            return *this;
        }
        ColDirection& ignore(const ColDirection& other)
        {
            return this->ignore(other.m_value);
        }
        [[nodiscard]] constexpr ColDirection ignored(const value_type& value)const
        {
            return  { static_cast<value_type>(m_value & static_cast<value_type>(~value)) };
        }
        [[nodiscard]] constexpr ColDirection ignored(const ColDirection& other)const
        {
            return this->ignored(other.m_value);
        }
        /// <summary>
        /// 速度から指定方向のあたり判定を無視する
        /// </summary>
        /// <param name="value"></param>
        /// <returns></returns>
        ColDirection& ignoreForVelocity(const s3d::Vec2& vellocity)
        {
            value_type ignore = None;
            if (vellocity.y > 0) {
                ignore |= Down;
            } else if (vellocity.y < 0) {
                ignore |= Up;
            }
            if (vellocity.x > 0) {
                ignore |= Right;
            } else if (vellocity.x < 0) {
                ignore |= Left;
            }
            return this->ignore(ignore);
        }

    public:
        static constexpr value_type None  = 0x00;
        static constexpr value_type Up    = 0x01;
        static constexpr value_type Down  = 0x02;
        static constexpr value_type Left  = 0x04;
        static constexpr value_type Right = 0x08;
        static constexpr value_type Vertical = Up | Down;
        static constexpr value_type Horizon = Left | Right;
        static constexpr value_type All   = Vertical | Horizon;
        static constexpr value_type ExceptDown = Up | Left | Right;
    };
}

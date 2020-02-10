#pragma once
#include <Siv3D/Fwd.hpp>

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

        explicit constexpr operator value_type() const
        {
            return m_value;
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

        constexpr ColDirection operator | (const ColDirection& other)const
        {
            return { static_cast<value_type>(m_value | other.m_value)};
        }

        constexpr ColDirection operator | (const value_type& value)const
        {
            return { static_cast<value_type>(m_value | value)};
        }

        friend ColDirection operator | (const value_type& left, const ColDirection& right)
        {
            return { static_cast<value_type>(left | right.m_value) };
        }
        constexpr ColDirection operator & (const ColDirection& other)const
        {
            return { static_cast<value_type>(m_value & other.m_value) };
        }

        constexpr ColDirection operator & (const value_type& value)const
        {
            return { static_cast<value_type>(m_value & value) };
        }

        friend ColDirection operator & (const value_type& left, const ColDirection& right)
        {
            return { static_cast<value_type>(left & right.m_value) };
        }

        constexpr bool operator == (const ColDirection& other)const
        {
            return m_value == other.m_value;
        }

        constexpr bool operator == (const value_type& value)const
        {
            return m_value == value;
        }

        friend bool operator == (const value_type& left, const ColDirection& right)
        {
            return left == right.m_value;
        }

        constexpr bool operator != (const ColDirection& other)const
        {
            return m_value != other.m_value;
        }

        constexpr bool operator != (const value_type& value)const
        {
            return m_value != value;
        }

        friend bool operator != (const value_type& left, const ColDirection& right)
        {
            return left != right.m_value;
        }

        constexpr operator bool() const
        {
            return m_value != 0;
        }

        constexpr bool isNone() const
        {
            return m_value == 0;
        }
    public:
        static constexpr value_type None  = 0x00;
        static constexpr value_type Up    = 0x01;
        static constexpr value_type Down  = 0x02;
        static constexpr value_type Left  = 0x04;
        static constexpr value_type Right = 0x08;
        static constexpr value_type All   = 0x0f;
    };
}
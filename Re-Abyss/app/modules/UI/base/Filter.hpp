#pragma once
#include <Siv3D/Types.hpp>

namespace abyss::UI
{
    class Filter
    {
    public:
        inline static constexpr s3d::uint32 None = 0x00;
        inline static constexpr s3d::uint32 Game = 0x1;
        inline static constexpr s3d::uint32 Event = 0x2;
        inline static constexpr s3d::uint32 Adv = 0x4;
        inline static constexpr s3d::uint32 Always = ~None;
    public:
        constexpr Filter():
            m_value(Always)
        {}

        constexpr Filter(s3d::uint32 value):
            m_value(value)
        {}

        constexpr bool isActive(const Filter& other) const
        {
            return (m_value & other.m_value) != 0;
        }
    private:
        s3d::uint32 m_value;
    };
}

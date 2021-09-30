#pragma once
#include <Siv3D/Duration.hpp>
#include <Siv3D/ISteadyClock.hpp>

namespace abyss::Clock
{
    struct CustomClock : s3d::ISteadyClock
    {
        CustomClock(const std::function<s3d::uint64()>& func);

        s3d::uint64 getMicrosec() override;
    private:
        std::function<s3d::uint64()> m_func;
    };


    struct CustomClockF : s3d::ISteadyClock
    {
        CustomClockF(const std::function<double()>& func);

        s3d::uint64 getMicrosec() override;
    private:
        std::function<double()> m_func;
    };
}
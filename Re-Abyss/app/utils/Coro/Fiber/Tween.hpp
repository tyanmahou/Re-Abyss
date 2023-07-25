#pragma once
#include <Siv3D/Duration.hpp>
#include <abyss/utils/Clock/Clock.hpp>
#include <abyss/utils/Coro/Fiber/Fiber.hpp>

namespace abyss::Coro
{
    class Tween
    {
    public:
        [[nodiscard]] static Fiber<> Sawtooth0_1(const s3d::Duration& duration, s3d::ISteadyClock* clock, std::function<void(double)> callback);
    };
}

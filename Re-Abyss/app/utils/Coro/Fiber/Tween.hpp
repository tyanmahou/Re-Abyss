#pragma once
#include <Siv3D/Duration.hpp>
#include <abyss/utils/Clock/Clock.hpp>
#include <abyss/utils/Coro/Fiber/Fiber.hpp>
#include <abyss/utils/Coro/AsyncGenerator/AsyncGenerator.hpp>

namespace abyss::Coro
{
    class Tween
    {
    public:
        [[nodiscard]] static Fiber<> Linear0_1(const s3d::Duration& duration, s3d::ISteadyClock* clock, std::function<void(double)> callback);
        [[nodiscard]] static AsyncGenerator<double> Linear0_1(const s3d::Duration& duration, s3d::ISteadyClock* clock = nullptr);

        [[nodiscard]] static Fiber<> Periodic(const s3d::Duration& duration, s3d::ISteadyClock* clock, double(*periodic)(const s3d::Duration&, double), std::function<void(double)> callback);
        [[nodiscard]] static Fiber<> Sine0_1(const s3d::Duration& duration, s3d::ISteadyClock* clock, std::function<void(double)> callback);
        [[nodiscard]] static Fiber<> Square0_1(const s3d::Duration& duration, s3d::ISteadyClock* clock, std::function<void(double)> callback);
        [[nodiscard]] static Fiber<> Pulse0_1(const s3d::Duration& duration, double dutyCycle, s3d::ISteadyClock* clock, std::function<void(double)> callback);
        [[nodiscard]] static Fiber<> Triangle0_1(const s3d::Duration& duration, s3d::ISteadyClock* clock, std::function<void(double)> callback);
        [[nodiscard]] static Fiber<> Sawtooth0_1(const s3d::Duration& duration, s3d::ISteadyClock* clock, std::function<void(double)> callback);
        [[nodiscard]] static Fiber<> Jump0_1(const s3d::Duration& duration, s3d::ISteadyClock* clock, std::function<void(double)> callback);
    };
}

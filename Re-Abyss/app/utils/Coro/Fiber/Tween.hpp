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
        [[nodiscard]] static AsyncGenerator<double> Linear(const s3d::Duration& duration, s3d::ISteadyClock* clock = nullptr);
        [[nodiscard]] static Fiber<> Linear(const s3d::Duration& duration, std::function<void(double)> callback, s3d::ISteadyClock* clock = nullptr);
        [[nodiscard]] static Fiber<> EaseIn(const s3d::Duration& duration, double(easing)(double), std::function<void(double)> callback, s3d::ISteadyClock* clock = nullptr);
        [[nodiscard]] static Fiber<> EaseOut(const s3d::Duration& duration, double(easing)(double), std::function<void(double)> callback, s3d::ISteadyClock* clock = nullptr);
        [[nodiscard]] static Fiber<> EaseInOut(const s3d::Duration& duration, double(easing)(double), std::function<void(double)> callback, s3d::ISteadyClock* clock = nullptr);

        [[nodiscard]] static Fiber<> Periodic(const s3d::Duration& duration, double(periodic)(const s3d::Duration&, double), std::function<void(double)> callback, s3d::ISteadyClock* clock = nullptr);
        [[nodiscard]] static Fiber<> Sine(const s3d::Duration& duration, std::function<void(double)> callback, s3d::ISteadyClock* clock = nullptr);
        [[nodiscard]] static Fiber<> Square(const s3d::Duration& duration, std::function<void(double)> callback, s3d::ISteadyClock* clock = nullptr);
        [[nodiscard]] static Fiber<> Pulse(const s3d::Duration& duration, double dutyCycle, std::function<void(double)> callback, s3d::ISteadyClock* clock = nullptr);
        [[nodiscard]] static Fiber<> Triangle(const s3d::Duration& duration, std::function<void(double)> callback, s3d::ISteadyClock* clock = nullptr);
        [[nodiscard]] static Fiber<> Sawtooth(const s3d::Duration& duration, std::function<void(double)> callback, s3d::ISteadyClock* clock = nullptr);
        [[nodiscard]] static Fiber<> Jump(const s3d::Duration& duration, std::function<void(double)> callback, s3d::ISteadyClock* clock = nullptr);
    };
}

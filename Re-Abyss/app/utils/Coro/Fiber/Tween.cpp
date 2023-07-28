#include <abyss/utils/Coro/Fiber/Tween.hpp>
#include "Tween.hpp"

namespace abyss::Coro
{
    Fiber<> Tween::Linear0_1(const s3d::Duration& duration, s3d::ISteadyClock* clock, std::function<void(double)> callback)
    {
        s3d::Timer timer(duration, StartImmediately::Yes, clock);
        while (!timer.reachedZero()) {
            callback(timer.progress0_1());
            co_yield{};
        }
        callback(1);
    }
    AsyncGenerator<double> Tween::Linear0_1(const s3d::Duration& duration, s3d::ISteadyClock* clock)
    {
        s3d::Timer timer(duration, StartImmediately::Yes, clock);
        while (!timer.reachedZero()) {
            co_yield timer.progress0_1();
            co_await Coro::Yield{};
        }
        co_yield 1.0;
    }
    Fiber<> Tween::Periodic(const s3d::Duration& duration, s3d::ISteadyClock* clock, double(*periodic)(const s3d::Duration&, double), std::function<void(double)> callback)
    {
        return Linear0_1(duration, clock, [periodic, callback](double v) {
            callback(periodic(1.0s, v));
        });
    }
    Fiber<> Tween::Sine0_1(const s3d::Duration& duration, s3d::ISteadyClock* clock, std::function<void(double)> callback)
    {
        return Periodic(duration, clock, &s3d::Periodic::Sine0_1, callback);
    }
    Fiber<> Tween::Square0_1(const s3d::Duration& duration, s3d::ISteadyClock* clock, std::function<void(double)> callback)
    {
        return Periodic(duration, clock, &s3d::Periodic::Square0_1, callback);
    }
    Fiber<> Tween::Pulse0_1(const s3d::Duration& duration, double dutyCycle, s3d::ISteadyClock* clock, std::function<void(double)> callback)
    {
        return Linear0_1(duration, clock, [dutyCycle, callback](double v) {
            callback(s3d::Periodic::Pulse0_1(1.0s, dutyCycle, v));
        });
    }
    Fiber<> Tween::Triangle0_1(const s3d::Duration& duration, s3d::ISteadyClock* clock, std::function<void(double)> callback)
    {
        return Periodic(duration, clock, &s3d::Periodic::Triangle0_1, callback);
    }
    Fiber<> Tween::Sawtooth0_1(const s3d::Duration& duration, s3d::ISteadyClock* clock, std::function<void(double)> callback)
    {
        return Periodic(duration, clock, &s3d::Periodic::Sawtooth0_1, callback);
    }
    Fiber<> Tween::Jump0_1(const s3d::Duration& duration, s3d::ISteadyClock* clock, std::function<void(double)> callback)
    {
        return Periodic(duration, clock, &s3d::Periodic::Jump0_1, callback);
    }
}

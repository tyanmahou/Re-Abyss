#include <abyss/utils/Coro/Fiber/Tween.hpp>

namespace abyss::Coro
{

    AsyncGenerator<double> Tween::Linear(const s3d::Duration& duration, s3d::ISteadyClock* clock)
    {
        s3d::Timer timer(duration, StartImmediately::Yes, clock);
        while (!timer.reachedZero()) {
            co_yield timer.progress0_1();
            co_await Coro::Yield{};
        }
        co_yield 1.0;
    }
    Fiber<> Tween::Linear(const s3d::Duration& duration, std::function<void(double)> callback, s3d::ISteadyClock* clock)
    {
        co_await Linear(duration, clock).each(callback);
    }
    Fiber<> Tween::EaseIn(const s3d::Duration& duration, double(easing)(double), std::function<void(double)> callback, s3d::ISteadyClock* clock)
    {
        return Linear(duration, [easing, callback](double v) {
            callback(s3d::EaseIn(easing, v));
        }, clock);
    }
    Fiber<> Tween::EaseOut(const s3d::Duration& duration, double(easing)(double), std::function<void(double)> callback, s3d::ISteadyClock* clock)
    {
        return Linear(duration, [easing, callback](double v) {
            callback(s3d::EaseOut(easing, v));
        }, clock);
    }
    Fiber<> Tween::EaseInOut(const s3d::Duration& duration, double(easing)(double), std::function<void(double)> callback, s3d::ISteadyClock* clock)
    {
        return Linear(duration, [easing, callback](double v) {
            callback(s3d::EaseInOut(easing, v));
        }, clock);
    }
    Fiber<> Tween::Periodic(const s3d::Duration& duration, double(periodic)(const s3d::Duration&, double), std::function<void(double)> callback, s3d::ISteadyClock* clock)
    {
        return Linear(duration, [periodic, callback](double v) {
            callback(periodic(1.0s, v));
        }, clock);
    }
    Fiber<> Tween::Sine(const s3d::Duration& duration, std::function<void(double)> callback, s3d::ISteadyClock* clock)
    {
        return Periodic(duration, s3d::Periodic::Sine0_1, callback, clock);
    }
    Fiber<> Tween::Square(const s3d::Duration& duration, std::function<void(double)> callback, s3d::ISteadyClock* clock)
    {
        return Periodic(duration, s3d::Periodic::Square0_1, callback, clock);
    }
    Fiber<> Tween::Pulse(const s3d::Duration& duration, double dutyCycle, std::function<void(double)> callback, s3d::ISteadyClock* clock)
    {
        return Linear(duration, [dutyCycle, callback](double v) {
            callback(s3d::Periodic::Pulse0_1(1.0s, dutyCycle, v));
        }, clock);
    }
    Fiber<> Tween::Triangle(const s3d::Duration& duration, std::function<void(double)> callback, s3d::ISteadyClock* clock)
    {
        return Periodic(duration, s3d::Periodic::Triangle0_1, callback, clock);
    }
    Fiber<> Tween::Sawtooth(const s3d::Duration& duration, std::function<void(double)> callback, s3d::ISteadyClock* clock)
    {
        return Periodic(duration, s3d::Periodic::Sawtooth0_1, callback, clock);
    }
    Fiber<> Tween::Jump(const s3d::Duration& duration, std::function<void(double)> callback, s3d::ISteadyClock* clock)
    {
        return Periodic(duration, s3d::Periodic::Jump0_1, callback, clock);
    }
}

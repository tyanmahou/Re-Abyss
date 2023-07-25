#include <abyss/utils/Coro/Fiber/Tween.hpp>

namespace abyss::Coro
{
    Fiber<> Tween::Sawtooth0_1(const s3d::Duration& duration, s3d::ISteadyClock* clock, std::function<void(double)> callback)
    {
        s3d::Timer timer(duration, StartImmediately::Yes, clock);
        while (!timer.reachedZero()) {
            callback(timer.progress0_1());
            co_yield{};
        }
        callback(1);
    }
}

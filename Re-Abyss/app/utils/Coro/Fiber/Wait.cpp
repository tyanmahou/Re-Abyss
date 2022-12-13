#include <abyss/utils/Coro/Fiber/Fiber.hpp>
#include <Siv3D.hpp>

namespace abyss::Coro
{
    Fiber<> WaitForSeconds(const s3d::Duration& duration)
    {
        Timer timer(duration, StartImmediately::Yes);
        while (!timer.reachedZero()) {
            co_yield{};
        }
    }

    Fiber<> WaitForSeconds(const s3d::Duration& duration, s3d::ISteadyClock* clock)
    {
        s3d::Timer timer(duration, StartImmediately::Yes, clock);
        while (!timer.reachedZero()) {
            co_yield{};
        }
    }
    Fiber<> WaitForFrame(s3d::int32 frame)
    {
        for (int32 count = 0; count < frame; ++count) {
            co_yield{};
        }
    }
    Fiber<> Stop()
    {
        while (true) {
            co_yield{};
        }
    }
}

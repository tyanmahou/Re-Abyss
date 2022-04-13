#include <abyss/utils/Coro/Task/Wait.hpp>
#include <Siv3D.hpp>
#include <abyss/utils/Coro/Task/Task.hpp>

namespace abyss::Coro
{
    Task<> WaitForSeconds(const s3d::Duration& duration)
    {
        Timer timer(duration, StartImmediately::Yes);
        while (!timer.reachedZero()) {
            co_yield{};
        }
    }

    Task<> WaitForSeconds(const s3d::Duration& duration, s3d::ISteadyClock* clock)
    {
        s3d::Timer timer(duration, StartImmediately::Yes, clock);
        while (!timer.reachedZero()) {
            co_yield{};
        }
    }
    Task<> WaitForFrame(s3d::int32 frame)
    {
        for (int32 count = 0; count < frame; ++count) {
            co_yield{};
        }
    }
    Task<> Stop()
    {
        while (true) {
            co_yield{};
        }
    }
}

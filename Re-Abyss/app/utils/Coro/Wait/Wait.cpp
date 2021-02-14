#include "Wait.hpp"

#include <Siv3D.hpp>

#include <abyss/utils/Coro/Task/Task.hpp>
#include <abyss/utils/TimerEx/TimerEx.hpp>

namespace abyss::Coro
{
    Task<> WaitForSeconds(const s3d::Duration& duration)
    {
        Timer timer(duration, true);
        while (!timer.reachedZero()) {
            co_yield{};
        }
    }

    Task<> WaitForSecondsEx(const s3d::Duration& duration, Clock_t timeGetter)
    {
        TimerEx timer(duration, true, timeGetter);
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
}

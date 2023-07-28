#include <abyss/utils/Coro/Fiber/Fiber.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>
#include <Siv3D.hpp>

namespace abyss::Coro
{
    Fiber<> WaitForSeconds(const s3d::Duration& duration)
    {
        TimeLite::Timer timer(duration.count());
        while (!timer.isEnd()) {
            timer.update(s3d::Scene::DeltaTime());
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
    Fiber<> WaitForFrame(s3d::uint32 frame)
    {
        co_yield{ frame };
    }
    Fiber<> Stop()
    {
        while (true) {
            co_yield{};
        }
    }
    Fiber<> Loop(std::function<void()> func)
    {
        while (true) {
            func();
            co_yield{};
        }
    }
    Fiber<> Loop(std::function<bool()> func)
    {
        while (true) {
            if (!func()) {
                break;
            }
            co_yield{};
        }
    }
    Fiber<> Loop(std::function<Fiber<>()> func)
    {
        while (true) {
            co_await func();
            co_yield{};
        }
    }
    Fiber<> Loop(std::function<Fiber<bool>()> func)
    {
        while (true) {
            if (bool result = co_await func(); !result) {
                break;
            }
            co_yield{};
        }
    }
}

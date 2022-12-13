#include <abyss/utils/Coro/Fiber/MultiFibers.hpp>

namespace abyss::Coro
{
	MultiFibers& MultiFibers::add(const std::function<Fiber<>()>& fiber)
	{
		m_fibers.push_back(fiber);
		return *this;
	}
	Fiber<> MultiFibers::whenAll() const
	{
        s3d::Array<Coro::Fiber<>> fibers;
        for (auto&& fiber : m_fibers) {
            fibers.push_back(fiber());
        }
        while (true) {
            for (auto&& fiber : fibers) {
                fiber.resume();
            }
            if (fibers.all([](const Coro::Fiber<>& fiber) {return fiber.isDone(); })) {
                break;
            }
            co_yield{};
        }
        co_return;
	}
	Fiber<> MultiFibers::whenAny() const
	{
        s3d::Array<Coro::Fiber<>> fibers;
        for (auto&& fiber : m_fibers) {
            fibers.push_back(fiber());
        }
        while (true) {
            for (auto&& fiber : fibers) {
                fiber.resume();
            }
            if (fibers.any([](const Coro::Fiber<>& fiber) {return fiber.isDone(); })) {
                break;
            }
            co_yield{};
        }
        co_return;
	}
}

#include <abyss/utils/Coro/Task/MultiTasks.hpp>

namespace abyss::Coro
{
	MultiTasks& MultiTasks::add(const std::function<Task<>()>& task)
	{
		m_tasks.push_back(task);
		return *this;
	}
	Task<> MultiTasks::operator()() const
	{
		s3d::Array<Coro::Task<>> tasks;
		for (auto&& task : m_tasks) {
			tasks.push_back(task());
		}
		while (true) {
			for (auto&& task : tasks) {
				task.moveNext();
			}
			if (tasks.all([](const Coro::Task<>& task) {return task.isDone(); })) {
				break;
			}
			co_yield{};
		}
		co_return;
	}
}

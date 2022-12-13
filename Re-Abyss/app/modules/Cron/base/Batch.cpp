#include <abyss/modules/Cron/base/Batch.hpp>
#include <abyss/components/Cron/base/IJob.hpp>
#include <abyss/components/Cron/base/IScheduler.hpp>

namespace abyss::Cron
{
    void Batch::reset()
    {
        auto jobs = this->finds<IJob>();
        if (jobs.isEmpty()) {
            return;
        }
        std::function<Coro::Fiber<>()> callback = [jobs]()->Coro::Fiber<> {
            s3d::Array<Coro::Fiber<>> tasks;
            for (auto& job : jobs) {
                tasks.push_back(job->onExecute());
            }
            while (true) {
                for (auto& task : tasks) {
                    task.resume();
                }

                if (tasks.all([](const Coro::Fiber<>& t) {return t.isDone(); })) {
                    co_return;
                }

                co_yield{};
            }
        };
        auto scheduler = this->find<IScheduler>();
        m_task = std::make_unique<Coro::Fiber<>>(scheduler->execute(callback));
    }

    bool Batch::update()
    {
        if (!m_task) {
            return false;
        }
        return m_task->resume();
    }
}

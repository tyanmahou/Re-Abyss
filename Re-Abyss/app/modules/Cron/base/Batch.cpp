#include "Batch.hpp"
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
        std::function<Coro::Task<>()> callback = [jobs]()->Coro::Task<> {
            s3d::Array<Coro::Task<>> tasks;
            for (auto& job : jobs) {
                tasks.push_back(job->onExecute());
            }
            while (true) {
                for (auto& task : tasks) {
                    task.moveNext();
                }

                if (tasks.all([](const Coro::Task<>& t) {return t.isDone(); })) {
                    co_return;
                }

                co_yield{};
            }
        };
        auto scheduler = this->find<IScheduler>();
        m_task = std::make_unique<Coro::Task<>>(scheduler->execute(callback));
    }

    bool Batch::update()
    {
        if (!m_task) {
            return false;
        }
        return m_task->moveNext();
    }
}

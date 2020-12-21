#include "Cron.hpp"
#include <abyss/modules/Cron/Common/IntervalTimeScheduler.hpp>
#include <abyss/modules/Cron/Common/OnceScheduler.hpp>

namespace abyss
{
    void Cron::update(double dt)
    {
        m_batchs.update(dt);
        m_batchs.erase();
    }
    Ref<cron::Batch> Cron::regist(const std::shared_ptr<cron::IJob> & job, const std::shared_ptr<cron::IScheduler>& scheduler)
    {
        job->setManager(m_pManager);
        scheduler->setManager(m_pManager);
        auto batch = std::make_shared <cron::Batch>(job, scheduler);
        m_batchs.push(batch);
        return batch;
    }
    Ref<cron::Batch> Cron::registOnce(const std::shared_ptr<cron::IJob>& job)
    {
        auto scheduler = std::make_shared<cron::OnceScheduler>();
        return this->regist(job, scheduler);
    }
    Ref<cron::Batch> Cron::registInterval(const std::shared_ptr<cron::IJob> & job, const s3d::Duration& duration)
    {
        auto scheduler = std::make_shared<cron::IntervalTimeScheduler>(duration);
        return this->regist(job, scheduler);
    }
}

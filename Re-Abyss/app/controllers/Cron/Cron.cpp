#include "Cron.hpp"
#include <abyss/controllers/Cron/Common/IntervalTimeScheduler.hpp>

namespace abyss
{
    void Cron::update(double dt)
    {
        m_batchs.update(dt);
        m_batchs.erase();
    }
    void Cron::regist(const std::shared_ptr<cron::IScheduler> & scheduler, const std::shared_ptr<cron::IJob> & job)
    {
        scheduler->setManager(m_pManager);
        job->setManager(m_pManager);
        m_batchs.push({ scheduler, job });
    }
    void Cron::regist(const s3d::Duration & duration, const std::shared_ptr<cron::IJob> & job)
    {
        auto scheduler = std::make_shared<cron::IntervalTimeScheduler>(duration);
        this->regist(scheduler, job);
    }
}

#include "Cron.hpp"

namespace abyss
{
    void Cron::update()
    {
        m_batchs.update();
        m_batchs.erase();
    }
    Ref<cron::Batch> Cron::create()
    {
        return this->regist(std::make_shared<cron::Batch>());
    }
    Ref<cron::Batch> Cron::regist(const std::shared_ptr<cron::Batch>& batch)
    {
        batch->setManager(m_pManager);
        m_batchs.push(batch);
        return batch;
    }
}

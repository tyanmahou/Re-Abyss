#include <abyss/modules/Cron/Crons.hpp>

namespace abyss
{
    void Crons::update()
    {
        m_batchs.update();
        m_batchs.erase();
    }
    Ref<Cron::Batch> Crons::create()
    {
        return this->regist(std::make_shared<Cron::Batch>());
    }
    Ref<Cron::Batch> Crons::regist(const std::shared_ptr<Cron::Batch>& batch)
    {
        batch->setManager(m_pManager);
        m_batchs.push(batch);
        return batch;
    }
}

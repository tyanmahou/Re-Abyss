#include "BatchHolder.hpp"

namespace abyss::cron
{
    void BatchHolder::flush()
    {
        if (m_reserves.empty()) {
            return;
        }
        // startでregistされてもいいようにここでmove
        auto registing = std::move(m_reserves);
        m_reserves.clear();
        for (auto& batch : registing) {
            batch.first->start();
            m_batchs.push_back(std::move(batch));
        }
    }
    void BatchHolder::push(const Batch& batch)
    {
        m_reserves.push_back(batch);
    }
    void BatchHolder::update(double dt)
    {
        this->flush();
        for (auto& batch : m_batchs) {
            if (!batch.first->update(dt)) {
                continue;
            }
            if (!batch.second->isActive()) {
                continue;
            }
            batch.second->onExecute();
        }
    }
    void BatchHolder::erase()
    {
        s3d::Erase_if(m_batchs, [](const Batch& batch) {
            return batch.second->isDestroyed();
        });
    }
    void BatchHolder::clear()
    {
        m_reserves.clear();
        m_batchs.clear();
    }
}


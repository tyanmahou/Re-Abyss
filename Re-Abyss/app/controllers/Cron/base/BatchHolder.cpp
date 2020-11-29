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
            m_batchs.push_back(std::move(batch));
        }
    }
    void BatchHolder::push(const std::shared_ptr<Batch>& batch)
    {
        m_reserves.push_back(batch);
    }
    void BatchHolder::update([[maybe_unused]]double dt)
    {
        this->flush();
        for (auto& batch : m_batchs) {
            if (!batch->isActive()) {
                continue;
            }
            if (!batch->update()) {
                batch->destroy();
            }
        }
    }
    void BatchHolder::erase()
    {
        s3d::Erase_if(m_batchs, [](const std::shared_ptr<Batch>& batch) {
            return batch->isDestroyed();
        });
    }
    void BatchHolder::clear()
    {
        m_reserves.clear();
        m_batchs.clear();
    }
}


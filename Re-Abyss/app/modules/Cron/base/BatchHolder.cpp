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
            batch->setup();
            batch->start();
            // task初期化
            batch->reset();
            m_batchs.push_back(std::move(batch));
        }
    }
    void BatchHolder::push(const std::shared_ptr<Batch>& batch)
    {
        m_reserves.push_back(batch);
    }
    void BatchHolder::update()
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
            if (batch->isDestroyed()) {
                batch->end();
                return true;
            }
            return false;
        });
    }
    void BatchHolder::clear()
    {
        m_reserves.clear();
        for (auto&& batch : m_batchs) {
            batch->end();
        }
        m_batchs.clear();
    }
}


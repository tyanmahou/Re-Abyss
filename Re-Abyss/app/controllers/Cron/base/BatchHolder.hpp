#pragma once
#include <memory>
#include <Siv3D/Array.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/concepts/UI.hpp>
#include <abyss/controllers/Cron/base/IJob.hpp>
#include <abyss/controllers/Cron/base/IScheduler.hpp>

namespace abyss::cron
{
    class BatchHolder
    {
    public:
        using Batch = std::pair<std::shared_ptr<IScheduler>, std::shared_ptr<IJob>>;
    private:
        s3d::Array<Batch> m_reserves;
        s3d::Array<Batch> m_batchs;

    public:
        void flush();
        void push(const Batch& batch);
        void update(double dt);
        void erase();

        void clear();
    };
}
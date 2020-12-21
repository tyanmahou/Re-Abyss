#pragma once
#include <memory>
#include <Siv3D/Array.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Cron/base/Batch.hpp>

namespace abyss::cron
{
    class BatchHolder
    {
    private:
        s3d::Array<std::shared_ptr<Batch>> m_reserves;
        s3d::Array<std::shared_ptr<Batch>> m_batchs;

    public:
        void flush();
        void push(const std::shared_ptr<Batch>& batch);
        void update();
        void erase();

        void clear();
    };
}
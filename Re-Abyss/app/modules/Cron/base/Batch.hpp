#pragma once
#include <memory>
#include <abyss/modules/GameObject/GameObject.hpp>
#include <abyss/utils/Coro/Task/Task.hpp>

namespace abyss::cron
{
    class Batch final : public GameObject
    {
        std::unique_ptr<Coro::Task<>> m_task;
    public:
        Batch() = default;

        void reset();

        bool update();
    };
}
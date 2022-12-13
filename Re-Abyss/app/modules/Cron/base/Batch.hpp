#pragma once
#include <memory>
#include <abyss/modules/GameObject/GameObject.hpp>
#include <abyss/utils/Coro/Fiber/Fiber.hpp>

namespace abyss::Cron
{
    class Batch final : public GameObject
    {
        std::unique_ptr<Coro::Fiber<>> m_task;
    public:
        Batch() = default;

        void reset();

        bool update();
    };
}
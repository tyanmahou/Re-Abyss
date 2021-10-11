#pragma once
#include <functional>
#include <abyss/utils/Coro/Task/Task.hpp>

namespace abyss::Coro
{
    template<class Type = void>
    class TaskHolder
    {
    public:
        TaskHolder() = default;

        void reset()
        {
            m_isReserve = true;
        }
        void reset(const std::function<Task<Type>()>& task)
        {
            m_taskFunc = task;
            this->reset();
        }
        void clear()
        {
            m_taskFunc = nullptr;
            this->reset();
        }
        bool moveNext()
        {
            if (m_isReserve) {
                // タスクを切り替え
                if (m_taskFunc) {
                    m_task = std::make_unique<Task<Type>>(m_taskFunc());
                } else {
                    m_task = nullptr;
                }
                m_isReserve = false;
            }

            if (m_task) {
                return m_task->moveNext();
            }
            return false;
        }
        bool isDone() const
        {
            if (m_task) {
                return m_task->isDone();
            }
            return true;
        }

    private:
        std::function<Task<Type>()> m_taskFunc;
        std::unique_ptr<Task<Type>> m_task;
        bool m_isReserve = false;
    };
}
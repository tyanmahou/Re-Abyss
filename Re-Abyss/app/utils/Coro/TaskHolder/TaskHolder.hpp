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
            if (m_taskFunc) {
                m_task = std::make_unique<Task<Type>>(m_taskFunc());
            } else {
                m_task = nullptr;
            }
        }
        void reset(const std::function<Task<Type>()>& task)
        {
            m_taskFunc = task;
            this->reset();
        }
        void clear()
        {
            m_taskFunc = nullptr;
            m_task = nullptr;
        }
        bool moveNext() const
        {
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
    };
}
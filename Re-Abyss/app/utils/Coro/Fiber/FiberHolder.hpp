#pragma once
#include <functional>
#include <abyss/utils/Coro/Fiber/Fiber.hpp>

namespace abyss::Coro
{
    template<class Type = void>
    class FiberHolder
    {
    public:
        FiberHolder() = default;

        void reset()
        {
            m_isReserve = true;
        }
        void reset(const std::function<Fiber<Type>()>& fiber)
        {
            m_fiberFunc = fiber;
            this->reset();
        }
        void clear()
        {
            m_fiberFunc = nullptr;
            this->reset();
        }
        bool resume()
        {
            if (m_isReserve) {
                // タスクを切り替え
                if (m_fiberFunc) {
                    m_fiber = std::make_unique<Fiber<Type>>(m_fiberFunc());
                } else {
                    m_fiber = nullptr;
                }
                m_isReserve = false;
            }

            if (m_fiber) {
                return m_fiber->resume();
            }
            return false;
        }
        bool isDone() const
        {
            if (m_isReserve) {
                return false;
            }
            if (m_fiber) {
                return m_fiber->isDone();
            }
            return true;
        }

    private:
        std::function<Fiber<Type>()> m_fiberFunc;
        std::unique_ptr<Fiber<Type>> m_fiber;
        bool m_isReserve = false;
    };
}

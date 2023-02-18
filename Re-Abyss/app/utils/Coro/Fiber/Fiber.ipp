#pragma once

namespace abyss::Coro
{
    template <class T>
    inline Fiber<T>::Fiber(Handle h) :
        m_coro(h)
    {}

    template <class T>
    inline Fiber<T>::Fiber(Fiber&& rhs) noexcept
        : m_coro(std::move(rhs.m_coro))
    {
        rhs.m_coro = nullptr;
    }
    template <class T>
    inline Fiber<T>::~Fiber()
    {
        if (m_coro) {
            m_coro.destroy();
        }
    }

    template <class T>
    inline bool Fiber<T>::resume() const
    {
        if (!m_coro) {
            return false;
        }
        if (m_coro.done()) {
            return false;
        }
        // Yield
        {
            auto& yield = m_coro.promise().yield;
            if (yield.count > 0 && yield.count-- > 0) {
                // カウンタが残ってるなら
                return true;
            }
        }
        // 割り込み別タスク
        {
            auto& next = m_coro.promise().next;
            if (next) {

                if (!next.resume()) {
                    next.clear();
                } else {
                    return true;
                }
            }
        }
        m_coro.resume();
        return !m_coro.done();
    }

    template <class T>
    inline bool Fiber<T>::isDone() const
    {
        if (!m_coro) {
            return true;
        }
        return m_coro.done();
    }

    template <class T>
    inline decltype(auto) Fiber<T>::get() const
    {
        return m_coro.promise().getValue();
    }

    template<class T, class U>
    inline Fiber<void> operator & (Fiber<T> a, Fiber<U> b)
    {
        while (true) {
            a.resume();
            b.resume();

            if (a.isDone() && b.isDone()) {
                co_return;
            }

            co_yield{};
        }
    }

    template<class T, class U>
    inline Fiber<void> operator | (Fiber<T> a, Fiber<U> b)
    {
        while (true) {
            a.resume();
            if (a.isDone()) {
                co_return;
            }
            b.resume();
            if (b.isDone()) {
                co_return;
            }

            co_yield{};
        }
    }

    template<class T, class U>
    inline Fiber<U> operator + (Fiber<T> a, Fiber<U> b)
    {
        while (a.resume()) {
            co_yield{};
        }
        while (b.resume()) {
            co_yield{};
        }
        co_return b.get();
    }
    namespace detail {
        template<class T>
        struct FiberAwaiter;
    }

    template<class T>
    inline auto operator co_await(Fiber<T> other)
    {
        return detail::FiberAwaiter{ std::move(other) };
    }

    namespace detail
    {
        /// <summary>
        /// NextFiberHandler
        /// </summary>
        struct NextFiberHandler
        {
        public:
            NextFiberHandler() = default;
            template<class T>
            NextFiberHandler(const Fiber<T>& fiber) :
                m_holder(std::make_unique<Holder<T>>(fiber))
            {}

            bool resume() const
            {
                return m_holder->resume();
            }
            void clear()
            {
                m_holder = nullptr;
            }
            explicit operator bool() const
            {
                return static_cast<bool>(m_holder);
            }
        private:
            struct IHolder
            {
                virtual ~IHolder() = default;
                virtual bool resume() const = 0;
            };
            template<class T>
            struct Holder final : IHolder
            {
                Holder(const Fiber<T>& fiber) :
                    m_fiber(fiber)
                {}
                bool resume() const override
                {
                    return m_fiber.resume();
                }
            private:
                const Fiber<T>& m_fiber;
            };
            std::unique_ptr<IHolder> m_holder;
        };

        /// <summary>
        /// Promise
        /// </summary>
        template<class T>
        struct PromiseValue
        {
            void return_value(const T& _value)
            {
                this->value = _value;
            }

            const T& getValue() const
            {
                return value;
            }
            T value;
        };

        // void特殊化
        template<>
        struct PromiseValue<void>
        {
            void return_void() {}

            void getValue() const
            {}
        };

        template<class T>
        struct PromiseType : PromiseValue<T>
        {
            using FiberType = Fiber<T>;

            static FiberType get_return_object_on_allocation_failure()
            {
                return FiberType{ nullptr };
            }
            auto get_return_object() { return FiberType{ FiberType::Handle::from_promise(*this) }; }
            auto initial_suspend() { return std::suspend_always{}; }
            auto final_suspend() noexcept { return std::suspend_always{}; }
            void unhandled_exception() { std::terminate(); }

            auto yield_value(const Yield& _yield)
            {
                return operator co_await(_yield);
            }
            Yield yield{ 0 };
            NextFiberHandler next;
        };

        template<class Handle>
        concept FiberAwaitableHandle = requires(Handle handle)
        {
            requires std::same_as<NextFiberHandler, decltype(handle.promise().next)>;
            requires std::convertible_to<Handle, std::coroutine_handle<>>;
        };

        /// <summary>
        /// Awaiter
        /// </summary>
        template<class T>
        struct FiberAwaiter
        {
            Fiber<T> fiber;

            bool await_ready() const
            {
                return !fiber.resume();
            }
            decltype(auto) await_resume() const
            {
                return fiber.get();
            }
            template<FiberAwaitableHandle Handle>
            void await_suspend(Handle handle) const
            {
                handle.promise().next = std::move(fiber);
            }
        };
    }
}

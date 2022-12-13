#pragma once
#include <coroutine>
#include <memory>
#include <abyss/utils/Coro/Fiber/Yield.hpp>

namespace abyss::Coro
{
    namespace detail
    {
        template<class Handle>
        concept YieldAwaitableHandle = requires(Handle handle)
        {
            requires std::same_as<Yield, decltype(handle.promise().yield)>;
            requires std::convertible_to<Handle, std::coroutine_handle<>>;
        };

        struct YieldAwaiter
        {
            bool await_ready() const noexcept
            {
                return yield.count == 0;
            }

            template<YieldAwaitableHandle Handle>
            void await_suspend(Handle handle)
            {
                --(handle.promise().yield = yield).count;
            }
            void await_resume() {}

            Yield yield;
        };
    }

    inline auto operator co_await(const Yield& yield)
    {
        return detail::YieldAwaiter{ yield };
    }

    namespace detail
    {
        template<class T>
        struct PromiseType;

        template<class T>
        struct FiberAwaiter;
    }

    /// <summary>
    /// Fiber
    /// </summary>
    template <class T = void>
    struct Fiber
    {
        using promise_type = detail::PromiseType<T>;
        using Handle = std::coroutine_handle<promise_type>;
    public:
        Fiber(Handle h) :
            coro(h)
        {}

        Fiber(Fiber const&) = delete;

        Fiber(Fiber&& rhs) noexcept
            : coro(std::move(rhs.coro))
        {
            rhs.coro = nullptr;
        }

        ~Fiber()
        {
            if (coro) {
                coro.destroy();
            }
        }
    public:
        /// <summary>
        /// 再開
        /// </summary>
        /// <returns></returns>
        bool resume() const
        {
            if (!coro) {
                return false;
            }
            if (coro.done()) {
                return false;
            }
            // Yield
            {
                auto& yield = coro.promise().yield;
                if (yield.count > 0 && yield.count-- > 0) {
                    // カウンタが残ってるなら
                    return true;
                }
            }
            // 割り込み別タスク
            {
                auto& next = coro.promise().next;
                if (next) {

                    if (!next.resume()) {
                        next.clear();
                    } else {
                        return true;
                    }
                }
            }
            coro.resume();
            return !coro.done();
        }

        /// <summary>
        /// 完了したか
        /// </summary>
        /// <returns></returns>
        [[nodiscard]] bool isDone()const
        {
            if (!coro) {
                return true;
            }
            return coro.done();
        }

        /// <summary>
        /// 取得
        /// </summary>
        /// <returns></returns>
        [[nodiscard]] decltype(auto) get() const
        {
            return coro.promise().getValue();
        }

    private:
        Handle coro;
    };

    template<class T>
    auto operator co_await(Fiber<T> other)
    {
        return detail::FiberAwaiter{ std::move(other) };
    }

    template<class T, class U>
    [[nodiscard]] Fiber<void> operator & (Fiber<T> a, Fiber<U> b)
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
    [[nodiscard]] Fiber<void> operator | (Fiber<T> a, Fiber<U> b)
    {
        while (true) {
            a.resume();
            b.resume();

            if (a.isDone() || b.isDone()) {
                co_return;
            }

            co_yield{};
        }
    }

    template<class T, class U>
    [[nodiscard]] Fiber<U> operator + (Fiber<T> a, Fiber<U> b)
    {
        while (a.resume()) {
            co_yield{};
        }
        while (b.resume()) {
            co_yield{};
        }
        co_return b.get();
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

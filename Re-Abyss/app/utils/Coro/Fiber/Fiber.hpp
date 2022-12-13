#pragma once
#include <coroutine>
#include <memory>
#include <abyss/utils/Coro/Fiber/Yield.hpp>

namespace abyss::Coro
{
    namespace detail
    {
        template<class T>
        struct PromiseType;
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
        Fiber(Handle h);

        Fiber(Fiber const&) = delete;

        Fiber(Fiber&& rhs) noexcept;

        ~Fiber();
    public:
        /// <summary>
        /// 再開
        /// </summary>
        /// <returns></returns>
        bool resume() const;

        /// <summary>
        /// 完了したか
        /// </summary>
        /// <returns></returns>
        [[nodiscard]] bool isDone() const;

        /// <summary>
        /// 取得
        /// </summary>
        /// <returns></returns>
        [[nodiscard]] decltype(auto) get() const;

    private:
        Handle m_coro;
    };

    /// <summary>
    /// operator co_await
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name="other"></param>
    /// <returns></returns>
    template<class T>
    auto operator co_await(Fiber<T> other);

    /// <summary>
    /// 両辺のFiberの完了を待つFiberを生成
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <typeparam name="U"></typeparam>
    /// <param name="a"></param>
    /// <param name="b"></param>
    /// <returns></returns>
    template<class T, class U>
    [[nodiscard]] Fiber<void> operator & (Fiber<T> a, Fiber<U> b);

    /// <summary>
    /// 両辺のいずれかのFiberの完了を待つFiberを生成
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <typeparam name="U"></typeparam>
    /// <param name="a"></param>
    /// <param name="b"></param>
    /// <returns></returns>
    template<class T, class U>
    [[nodiscard]] Fiber<void> operator | (Fiber<T> a, Fiber<U> b);

    /// <summary>
    /// 左辺のFiberの完了を待ったあと右辺のFiberを待つ
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <typeparam name="U"></typeparam>
    /// <param name="a"></param>
    /// <param name="b"></param>
    /// <returns></returns>
    template<class T, class U>
    [[nodiscard]] Fiber<U> operator + (Fiber<T> a, Fiber<U> b);
}

#include "Fiber.ipp"

//#pragma once
//#include <coroutine>
//#include <abyss/utils/Coro/Task/Wait.hpp>
//
//namespace abyss::Coro
//{
//	template<class Type>
//	struct AsyncGenerator
//	{
//        struct promise_type;
//        using handle = std::coroutine_handle<promise_type>;
//
//        struct promise_type
//        {
//            Type value;
//            auto get_return_object() { return AsyncGenerator{ handle::from_promise(*this) }; }
//            auto  initial_suspend() { return std::suspend_never{}; }
//            auto final_suspend() noexcept { return std::suspend_always{}; }
//            auto yield_value(const Type& _value)
//            {
//                this->value = _value;
//                isFindValue = true;
//                return std::suspend_always{};
//            }
//            void unhandled_exception() { std::terminate(); }
//            void return_void() {}
//
//            detail::NextTaskHandler next;
//            bool isFindValue = false;
//        };
//
//        struct iterator
//        {
//            const AsyncGenerator* owner;
//            Task<iterator> operator++()
//            {
//                owner->coro.promise().isFindValue = false;
//                while (owner->moveNext()) {
//                    co_yield;
//                }
//                co_return { owner };
//            }
//            decltype(auto) operator*()
//            {
//                return owner->coro.promise().value;
//            }
//            bool operator!=(const iterator&) const
//            {
//                return (!owner || !owner->coro.done());
//            }
//        };
//    public:
//        Task<iterator> begin() const
//        {
//            coro.promise().isFindValue = false;
//            while (this->moveNext()) {
//                co_yield;
//            }
//            co_return { this };
//        }
//        iterator end()const { return { nullptr }; }
//    public:
//        explicit AsyncGenerator(handle h)
//            : coro(h)
//        {}
//
//        AsyncGenerator(const AsyncGenerator&) = delete;
//
//        AsyncGenerator(AsyncGenerator&& rhs) noexcept
//            : coro(std::move(rhs.coro))
//        {
//            rhs.coro = nullptr;
//        }
//
//        ~AsyncGenerator()
//        {
//            if (coro) {
//                coro.destroy();
//            }
//        }
//    private:
//        /// <summary>
//        /// 再開
//        /// </summary>
//        /// <returns></returns>
//        bool moveNext() const
//        {
//            if (!coro) {
//                return false;
//            }
//            if (coro.done()) {
//                return false;
//            }
//            // 割り込み別タスク
//            {
//                auto& next = coro.promise().next;
//                if (next) {
//
//                    if (!next.moveNext()) {
//                        next.clear();
//                    } else {
//                        return true;
//                    }
//                }
//            }
//            coro.resume();
//            return !coro.promise().isFindValue && !coro.done();
//        }
//    private:
//        handle coro;
//	};
//}
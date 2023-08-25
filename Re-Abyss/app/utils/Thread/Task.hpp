#pragma once
#include <future>
#include <stop_token>
#include <Siv3D/Duration.hpp>
#include <abyss/utils/Coro/Fiber/IAwaiter.hpp>

namespace abyss::Thread
{
    template<class Type>
    class Task
    {
    public:
        Task() = default;
        Task(Task&& task):
            m_stopSource(std::move(task.m_stopSource)),
            m_future(std::move(task.m_future))
        {}
        template<class Func, class... Args> requires std::is_invocable_r_v<Type, Func, Args...>
        Task(Func&& func, Args&&... args) :
            Task(std::launch::async, std::forward<Func>(func), std::forward<Args>(args)...)
        {
        }
        template<class Func, class... Args> requires std::is_invocable_r_v<Type, Func, Args...>
        Task(std::launch policy, Func&& func, Args&&... args) :
            m_future(std::async(policy, std::forward<Func>(func), std::forward<Args>(args)...))
        {
        }
        template<class Func, class... Args> requires std::is_invocable_r_v<Type, Func, std::stop_token, Args...>
        Task(Func&& func, Args&&... args) :
            Task(std::launch::async, std::forward<Func>(func), std::forward<Args>(args)...)
        {
        }
        template<class Func, class... Args> requires std::is_invocable_r_v<Type, Func, std::stop_token, Args...>
        Task(std::launch policy, Func&& func, Args&&... args) :
            m_future(std::async(policy, std::forward<Func>(func), m_stopSource.get_token(), std::forward<Args>(args)...))
        {
        }
        template<class Func, class... Args> requires std::is_invocable_r_v<Type, Func, std::stop_token, Args...>
        Task(const std::stop_source& stopSource, Func&& func, Args&&... args) :
            Task(std::launch::async, stopSource, std::forward<Func>(func), std::forward<Args>(args)...)
        {
        }
        template<class Func, class... Args> requires std::is_invocable_r_v<Type, Func, std::stop_token, Args...>
        Task(std::launch policy, const std::stop_source& stopSource, Func&& func, Args&&... args) :
            m_stopSource(stopSource),
            m_future(std::async(policy, std::forward<Func>(func), stopSource.get_token(), std::forward<Args>(args)...))
        {
        }

        ~Task()
        {
            this->request_stop();
        }
        inline decltype(auto) get()
        {
            return m_future.get();
        }

        inline void wait() const
        {
            return m_future.wait();
        }
        template <class Rep, class Period>
        std::future_status wait_for(const std::chrono::duration<Rep, Period>& relTime) const
        {
            return m_future.wait_for(relTime);
        }

        template <class Clock, class Duration>
        std::future_status wait_until(const std::chrono::time_point<Clock, Duration>& absTime) const
        {
            return m_future.wait_until(absTime);
        }

        bool isBusy() const
        {
            if (!isValid()) {
                return false;
            }
            return isTimeout(0s);
        }

        bool isReady() const
        {
            return isReady(0s);
        }
        bool isReady(const s3d::Duration& duration) const
        {
            return wait_for(duration) == std::future_status::ready;
        }
        bool isTimeout(const s3d::Duration& duration) const
        {
            return wait_for(duration) == std::future_status::timeout;
        }
        inline bool request_stop() noexcept
        {
            return m_stopSource.request_stop();
        }
        inline std::stop_token get_token() const noexcept
        {
            return m_stopSource.get_token();
        }
        inline bool isValid() const noexcept
        {
            return m_future.valid();
        }
        inline bool valid() const noexcept
        {
            return m_future.valid();
        }
        explicit operator bool() const noexcept
        {
            return valid();
        }
    private:
        std::stop_source m_stopSource;
        std::future<Type> m_future;
    };

    namespace detail
    {
        template<class T, class... Args>
        struct TaskResult
        {
        };
        template<class Func, class... Args> requires std::is_invocable_v<Func, Args...>
        struct TaskResult<Func, Args...>
        {
            using Type = std::invoke_result_t<Func, Args...>;
        };
        template<class Func, class... Args> requires std::is_invocable_v<Func, std::stop_token, Args...>
        struct TaskResult<Func, Args...>
        {
            using Type = std::invoke_result_t<Func, std::stop_token, Args...>;
        };
        template<class Func, class... Args>
        using TaskResult_t = typename TaskResult<Func, Args...>::Type;
    }
    template<class Func, class... Args>
    Task(Func, Args...) -> Task<detail::TaskResult_t<Func, Args...>>;
    template<class Func, class... Args>
    Task(std::launch, Func, Args...) -> Task<detail::TaskResult_t<Func, Args...>>;
    template<class Func, class... Args>
    Task(const std::stop_source&, Func, Args...) -> Task<detail::TaskResult_t<Func, Args...>>;
    template<class Func, class... Args>
    Task(std::launch, const std::stop_source&, Func, Args...) -> Task<detail::TaskResult_t<Func, Args...>>;

    template<class T>
    struct TaskAwaiter : Coro::IAwaiter
    {
        TaskAwaiter(Task<T>&& _task) :
            task(std::move(_task))
        {}
        bool await_ready() noexcept
        {
            return !resume();
        }

        template<Coro::AwaitableHandler Handle>
        void await_suspend(Handle handle)
        {
            handle.promise().pAwaiter = this;
        }
        decltype(auto) await_resume()
        {
            return task.get();
        }

        bool resume() override
        {
            return task.isBusy();
        }
        Task<T> task;
    };

    template<class T>
    inline auto operator co_await(Task<T> task)
    {
        return TaskAwaiter{ std::move(task) };
    }
}

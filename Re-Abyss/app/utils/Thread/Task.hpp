#pragma once
#include <future>
#include <stop_token>
#include <Siv3D/Duration.hpp>

namespace abyss::Thread
{
    template<class T>
    class Task
    {
    public:
        Task() = default;
        template<class Func, class... Args> requires std::is_invocable_r_v<T, Func, Args...>
        Task(Func&& func, Args&&... args) :
            _future(std::async(std::launch::async, std::forward<Func>(func), std::forward<Args>(args)...))
        {
        }
        template<class Func, class... Args> requires std::is_invocable_r_v<T, Func, Args...>
        Task(Func&& func, std::launch policy, Args&&... args) :
            _future(std::async(policy, std::forward<Func>(func), std::forward<Args>(args)...))
        {
        }
        template<class Func, class... Args> requires std::is_invocable_r_v<T, Func, std::stop_token, Args...>
        Task(Func&& func, Args&&... args):
            _future(std::async(std::launch::async, std::forward<Func>(func), _stopSource.get_token(), std::forward<Args>(args)...))
        {
        }
        template<class Func, class... Args> requires std::is_invocable_r_v<T, Func, std::stop_token, Args...>
        Task(Func&& func, std::launch policy, Args&&... args) :
            _future(std::async(policy, std::forward<Func>(func), _stopSource.get_token(), std::forward<Args>(args)...))
        {
        }

        ~Task()
        {
            this->requestStop();
        }
        inline decltype(auto) get()
        {
            return _future.get();
        }

        std::future_status wait_for(s3d::Duration duration) const
        {
            return _future.wait_for(duration);
        }
        bool isBusy() const
        {
            if (!isValid()) {
                return false;
            }
            return !isReady();
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
        inline bool requestStop() noexcept
        {
            return _stopSource.request_stop();
        }
        inline bool isValid() const noexcept
        {
            return _future.valid();
        }
    private:
        std::stop_source _stopSource;
        std::future<T> _future;
    };
}

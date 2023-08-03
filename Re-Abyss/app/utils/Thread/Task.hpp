#pragma once
#include <future>

namespace abyss::Thread
{
    template<class T>
    class Task
    {
    public:
        template<class Func, class... Args>
        Task(Func&& func, Args&&... args):
            _future(std::async(std::launch::async, std::forward<Func>(func), _stopSource.get_token(), std::forward<Args>(args)...))
        {
        }
        ~Task()
        {
            _stopSource.request_stop();
        }
        decltype(auto) get()
        {
            return _future.get();
        }

        bool isBusy() const
        {
            return _future.wait_for(0s) != std::future_status::ready;
        }
    private:
        std::stop_source _stopSource;
        std::future<T> _future;
    };
}

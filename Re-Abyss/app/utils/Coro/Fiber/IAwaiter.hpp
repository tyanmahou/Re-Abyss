#pragma once
#include <coroutine>

namespace abyss::Coro
{
    struct IAwaiter
    {
    public:
        virtual ~IAwaiter() = default;

        virtual bool resume() = 0;
    };

    template<class Handle>
    concept AwaitableHandler = requires(Handle handle)
    {
        requires std::same_as<IAwaiter*, decltype(handle.promise().pAwaiter)>;
        requires std::convertible_to<Handle, std::coroutine_handle<>>;
    };
}

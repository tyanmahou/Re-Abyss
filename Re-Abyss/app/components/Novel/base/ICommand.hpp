#pragma once
#include <abyss/utils/Coro/Task/Task.hpp>

namespace abyss::Novel
{
    class ICommand
    {
    public:
        virtual ~ICommand() = default;

        virtual void onStart() {}
        virtual void onEnd() {}
        virtual Coro::Task<> onCommand() = 0;
    };
}
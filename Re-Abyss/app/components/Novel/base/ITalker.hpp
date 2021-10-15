#pragma once
#include <abyss/utils/Coro/Task/Task.hpp>

namespace abyss::Novel
{
    class ITalker
    {
    public:
        virtual ~ITalker() = default;

        virtual void onStart() {}
        virtual void onEnd() {}
        virtual Coro::Task<> onTalk() = 0;
    };
}
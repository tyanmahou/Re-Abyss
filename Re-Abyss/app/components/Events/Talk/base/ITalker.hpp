#pragma once
#include <abyss/utils/Coro/Task/Task.hpp>

namespace abyss::Event::Talk
{
    class ITalker
    {
    public:
        virtual ~ITalker() = default;

        virtual Coro::Task<> onTalk() = 0;
    };
}
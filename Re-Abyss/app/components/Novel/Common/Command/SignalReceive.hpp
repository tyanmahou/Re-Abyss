#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Novel/base/ICommand.hpp>

namespace abyss::Novel
{
    class SignalReceive :
        public ICommand
    {
    private:
        using FunctionType = bool(*)(TalkObj*);
    public:
        SignalReceive(TalkObj* pTalk, FunctionType func);

        void onStart() override;
        Coro::Fiber<> onCommand() override;
    private:
        TalkObj* m_pTalk = nullptr;
        FunctionType m_func;
    };
}
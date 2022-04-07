#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Novel/base/ICommand.hpp>

namespace abyss::Novel
{
    class Signal :
        public ICommand
    {
    private:
        using FunctionType = void(*)(TalkObj*);
    public:
        Signal(TalkObj* pTalk, FunctionType func);

        void onStart() override;
        Coro::Task<> onCommand() override;
    private:
        TalkObj* m_pTalk = nullptr;
        FunctionType m_func;
    };
}
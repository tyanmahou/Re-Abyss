#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Adv/base/ICommand.hpp>

namespace abyss::Adv
{
    class SignalSend :
        public ICommand
    {
    private:
        using FunctionType = void(*)(AdvObj*);
    public:
        SignalSend(AdvObj* pTalk, FunctionType func);

        void onStart() override;
        Coro::Fiber<> onCommand() override;
    private:
        AdvObj* m_pTalk = nullptr;
        FunctionType m_func;
    };
}

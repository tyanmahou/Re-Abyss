#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Adv/base/ICommand.hpp>

namespace abyss::Adv
{
    class SignalReceive :
        public ICommand
    {
    private:
        using FunctionType = bool(*)(AdvObj*);
    public:
        SignalReceive(AdvObj* pTalk, FunctionType func);

        void onStart() override;
        Coro::Fiber<> onCommand() override;
    private:
        AdvObj* m_pTalk = nullptr;
        FunctionType m_func;
    };
}

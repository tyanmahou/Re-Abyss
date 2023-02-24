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
        SignalReceive(AdvObj* pObj, FunctionType func);

        void onStart() override;
        Coro::Fiber<> onCommand() override;
    private:
        AdvObj* m_pObj = nullptr;
        FunctionType m_func;
    };
}

#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Adv/base/ICommand.hpp>

namespace abyss::Adv
{
    class WaitInput :
        public ICommand
    {
    public:
        WaitInput(AdvObj* pObj);

        void onStart() override;
        void onEnd() override;

        Coro::Fiber<> onCommand() override;
    private:
        AdvObj* m_pObj = nullptr;
    };
}

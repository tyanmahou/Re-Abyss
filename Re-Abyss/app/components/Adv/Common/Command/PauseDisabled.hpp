#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Adv/base/ICommand.hpp>

namespace abyss::Adv
{
    class PauseDisabled :
        public ICommand
    {
    public:
        PauseDisabled(AdvObj* pTalk, bool isDisabled);

        void onStart() override;
        Coro::Fiber<> onCommand() override;
    private:
        AdvObj* m_pTalk = nullptr;
        bool m_isDisabled = false;
    };
}

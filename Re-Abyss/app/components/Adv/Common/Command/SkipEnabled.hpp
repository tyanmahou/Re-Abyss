#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Adv/base/ICommand.hpp>

namespace abyss::Adv
{
    class SkipEnabled :
        public ICommand
    {
    public:
        SkipEnabled(AdvObj* pTalk, bool isEnabled);

        void onStart() override;
        Coro::Fiber<> onCommand() override;
    private:
        AdvObj* m_pTalk = nullptr;
        bool m_isEnabled = false;
    };
}

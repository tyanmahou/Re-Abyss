#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Adv/base/ICommand.hpp>

namespace abyss::Adv
{
    class SkipEnabled :
        public ICommand
    {
    public:
        SkipEnabled(AdvObj* pObj, bool isEnabled);

        void onStart() override;
        Coro::Fiber<> onCommand() override;
    private:
        AdvObj* m_pObj = nullptr;
        bool m_isEnabled = false;
    };
}

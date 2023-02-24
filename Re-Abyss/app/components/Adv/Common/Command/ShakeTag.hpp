#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Adv/base/ICommand.hpp>

namespace abyss::Adv
{
    class ShakeTag :
        public ICommand
    {
    public:
        ShakeTag(AdvObj* pTalk, bool isShake);

        void onStart() override;
        Coro::Fiber<> onCommand() override;
    private:
        AdvObj* m_pTalk = nullptr;
        bool m_isShake;
    };
}

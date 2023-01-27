#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Novel/base/ICommand.hpp>

namespace abyss::Novel
{
    class ShakeTag :
        public ICommand
    {
    public:
        ShakeTag(TalkObj* pTalk, bool isShake);

        void onStart() override;
        Coro::Fiber<> onCommand() override;
    private:
        TalkObj* m_pTalk = nullptr;
        bool m_isShake;
    };
}

#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Novel/base/ICommand.hpp>

namespace abyss::Novel
{
    class PauseDisabled :
        public ICommand
    {
    public:
        PauseDisabled(TalkObj* pTalk, bool isDisabled);

        void onStart() override;
        Coro::Fiber<> onCommand() override;
    private:
        TalkObj* m_pTalk = nullptr;
        bool m_isDisabled = false;
    };
}

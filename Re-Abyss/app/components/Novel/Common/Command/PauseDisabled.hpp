#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Novel/base/ICommand.hpp>

namespace abyss::Novel
{
    class PauseDisabled :
        public ICommand
    {
    public:
        PauseDisabled(TalkObj* pTalk, bool isDisabled);

        void onStart() override;
        Coro::Task<> onCommand() override;
    private:
        TalkObj* m_pTalk = nullptr;
        bool m_isDisabled = false;
    };
}

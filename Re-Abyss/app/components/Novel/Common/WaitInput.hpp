#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Novel/base/ICommand.hpp>

namespace abyss::Novel
{
    class WaitInput :
        public ICommand
    {
    public:
        WaitInput(TalkObj* pTalk);

        void onStart() override;
        void onEnd() override;

        Coro::Task<> onCommand() override;
    private:
        TalkObj* m_pTalk = nullptr;
    };
}
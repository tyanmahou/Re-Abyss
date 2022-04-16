#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Novel/base/ICommand.hpp>

namespace abyss::Novel::BossTalk0_1
{
    class Setup : 
        public ICommand
    {
    public:
        Setup(TalkObj* pTalk);

        void onStart() override;

        Coro::Task<> onCommand() override;

    private:
        TalkObj* m_pTalk;
    };
}
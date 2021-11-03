#pragma once
#include <abyss/commons/Fwd.hpp>

#include <abyss/components/Novel/base/ICommand.hpp>

namespace abyss::Novel::BossTalk0_0
{
    class Teardown :
        public ICommand
    {
    public:
        Teardown(TalkObj* pTalk);

        void onStart() override;

        Coro::Task<> onCommand() override;

    private:
        TalkObj* m_pTalk;
    };
}
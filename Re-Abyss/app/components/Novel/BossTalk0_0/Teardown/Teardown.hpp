#pragma once
#include <abyss/commons/Fwd.hpp>

#include <abyss/components/Novel/base/ITalker.hpp>

namespace abyss::Novel::BossTalk0_0
{
    class Teardown :
        public ITalker
    {
    public:
        Teardown(TalkObj* pTalk);

        void onStart() override;

        Coro::Task<> onTalk() override;

    private:
        TalkObj* m_pTalk;
    };
}
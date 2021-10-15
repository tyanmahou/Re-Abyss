#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Novel/base/ITalker.hpp>

namespace abyss::Novel::BossTalk0_0
{
    class Setup : 
        public ITalker
    {
    public:
        Setup(TalkObj* pTalk);

        void onStart() override;

        Coro::Task<> onTalk() override;

    private:
        TalkObj* m_pTalk;
    };
}
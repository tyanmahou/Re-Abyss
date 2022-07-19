#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Novel/base/ICommand.hpp>

namespace abyss::Novel
{
    class Stash :
        public ICommand
    {
    public:
        Stash(TalkObj* pTalk);

        void onStart() override;
        Coro::Task<> onCommand() override;
    private:
        TalkObj* m_pTalk = nullptr;
    };
}

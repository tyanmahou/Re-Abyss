#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Novel/base/ICommand.hpp>

namespace abyss::Novel::CodeZeroDemo
{
    class DisappearEnd :
        public ICommand
    {
    public:
        DisappearEnd(TalkObj* pTalk);

        void onStart() override;

        Coro::Fiber<> onCommand() override;

    private:
        TalkObj* m_pTalk;
    };
}

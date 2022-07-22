#pragma once
#include <abyss/commons/Fwd.hpp>

#include <abyss/components/Novel/base/ICommand.hpp>

namespace abyss::Novel::CodeZeroDemo
{
    class AppearEnd :
        public ICommand
    {
    public:
        AppearEnd(TalkObj* pTalk);

        void onStart() override;

        Coro::Task<> onCommand() override;

    private:
        TalkObj* m_pTalk;
    };
}

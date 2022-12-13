#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Novel/base/ICommand.hpp>

namespace abyss::Novel
{
    class SkipEnabled :
        public ICommand
    {
    public:
        SkipEnabled(TalkObj* pTalk, bool isEnabled);

        void onStart() override;
        Coro::Fiber<> onCommand() override;
    private:
        TalkObj* m_pTalk = nullptr;
        bool m_isEnabled = false;
    };
}

#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Novel/base/ICommand.hpp>
#include <Siv3D/Optional.hpp>
#include <Siv3D/ColorF.hpp>

namespace abyss::Novel
{
    class ClearMessage :
        public ICommand
    {
    public:
        ClearMessage(TalkObj* pTalk);

        void onStart() override;
        Coro::Fiber<> onCommand() override;
    private:
        TalkObj* m_pTalk = nullptr;
    };
}

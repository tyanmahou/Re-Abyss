#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Novel/base/ICommand.hpp>
#include <Siv3D/Optional.hpp>
#include <Siv3D/ColorF.hpp>

namespace abyss::Novel
{
    class ShowHideMessage :
        public ICommand
    {
    public:
        ShowHideMessage(TalkObj* pTalk, bool isShow);

        void onStart() override;
        void onEnd() override;
        Coro::Fiber<> onCommand() override;
    private:
        TalkObj* m_pTalk = nullptr;
        bool m_isShow = false;
    };
}

#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Adv/base/ICommand.hpp>
#include <Siv3D/Optional.hpp>
#include <Siv3D/ColorF.hpp>

namespace abyss::Adv
{
    class ShowHideMessage :
        public ICommand
    {
    public:
        ShowHideMessage(AdvObj* pTalk, bool isShow);

        void onStart() override;
        void onEnd() override;
        Coro::Fiber<> onCommand() override;
    private:
        AdvObj* m_pTalk = nullptr;
        bool m_isShow = false;
    };
}

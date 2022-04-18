#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>

namespace abyss::Novel::BossTalk0_1
{
    class SignalCtrl : public IComponent
    {
    public:
        SignalCtrl(TalkObj* pTalk);
    private:
        TalkObj* m_pTalk;
    };
}
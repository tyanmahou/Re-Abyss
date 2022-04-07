#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>

namespace abyss::Novel::BossTalk0_0
{
    class SignalCtrl : public IComponent
    {
    public:
        SignalCtrl(TalkObj* pTalk):
            m_pTalk(pTalk)
        {}

        bool isRequestedAppear() const
        {
            return m_requestedAppear;
        }
        void requestAppear()
        {
            m_requestedAppear = true;
        }
    private:
        TalkObj* m_pTalk;

        bool m_requestedAppear = false;
    };
}
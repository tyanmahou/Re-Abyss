#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/utils/Reflection/Reflection.hpp>

namespace abyss::Novel::BossTalk0_0
{
    class SignalCtrl : public IComponent
    {
    public:
        [[REFLECTION(RequestAppear)]]
        static void RequestAppear(TalkObj* pTalk);
    public:
        SignalCtrl(TalkObj* pTalk);

        bool isRequestedAppear() const
        {
            return m_requestedAppear;
        }
    private:
        void requestAppear()
        {
            m_requestedAppear = true;
        }
    private:
        TalkObj* m_pTalk;

        bool m_requestedAppear = false;
    };
}
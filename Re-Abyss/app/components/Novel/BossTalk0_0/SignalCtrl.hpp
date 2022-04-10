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
        [[REFLECTION(IsAppearEnd)]]
        static bool IsAppearEnd(TalkObj* pTalk);
    public:
        SignalCtrl(TalkObj* pTalk);

        const TalkObj* getObj() const
        {
            return m_pTalk;
        }

        bool isRequestedAppear() const
        {
            return m_requestedAppear;
        }
        void setAppearEnd()
        {
            m_isAppearEnd = true;
        }
    private:
        void requestAppear()
        {
            m_requestedAppear = true;
        }
        bool isAppearEnd() const
        {
            return m_isAppearEnd;
        }
    private:
        TalkObj* m_pTalk;

        bool m_requestedAppear = false;
        bool m_isAppearEnd = false;
    };
}
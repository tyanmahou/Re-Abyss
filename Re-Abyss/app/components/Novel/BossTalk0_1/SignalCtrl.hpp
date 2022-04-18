#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/utils/Reflection/Reflection.hpp>

namespace abyss::Novel::BossTalk0_1
{
    class SignalCtrl : public IComponent
    {
    public:
        [[REFLECTION(RequestDead)]]
        static void RequestDead(TalkObj* pTalk);
        [[REFLECTION(IsDeadEnd)]]
        static bool IsDeadEnd(TalkObj* pTalk);
    public:
        SignalCtrl(TalkObj* pTalk);

        bool isRequestedDead() const
        {
            return m_requestedDead;
        }
        void setDeadEnd()
        {
            m_isDeadEnd = true;
        }
    private:
        void requestDead()
        {
            m_requestedDead = true;
        }
        bool isDeadEnd() const
        {
            return m_isDeadEnd;
        }
    private:
        TalkObj* m_pTalk;

        bool m_requestedDead = false;
        bool m_isDeadEnd = false;
    };
}
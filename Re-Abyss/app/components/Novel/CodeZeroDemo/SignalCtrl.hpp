#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/utils/Reflection/Reflection.hpp>

namespace abyss::Novel::CodeZeroDemo
{
    class SignalCtrl : public IComponent
    {
    public:
        [[REFLECTION(RequestAppear)]]
        static void RequestAppear(TalkObj* pTalk);
        [[REFLECTION(IsAppearEnd)]]
        static bool IsAppearEnd(TalkObj* pTalk);

        [[REFLECTION(RequestBattleStart)]]
        static void RequestBattleStart(TalkObj* pTalk);
        [[REFLECTION(IsBattleEnd)]]
        static bool IsBattleEnd(TalkObj* pTalk);

        [[REFLECTION(RequestDead)]]
        static void RequestDead(TalkObj* pTalk);
        [[REFLECTION(IsDeadEnd)]]
        static bool IsDeadEnd(TalkObj* pTalk);
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
        bool isBattleStart() const
        {
            return m_isBattleStart;
        }
        void requestBattleEnd()
        {
            m_isBattleEnd = true;
        }
        bool isRequestedDead() const
        {
            return m_requestedDead;
        }
        void setDeadEnd()
        {
            m_isDeadEnd = true;
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
        void requestBattleStart()
        {
            m_isBattleStart = true;
        }
        bool isBattleEnd() const
        {
            return m_isBattleEnd;
        }
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

        bool m_requestedAppear = false;
        bool m_isAppearEnd = false;

        bool m_isBattleStart = false;
        bool m_isBattleEnd = false;

        bool m_requestedDead = false;
        bool m_isDeadEnd = false;
    };
}

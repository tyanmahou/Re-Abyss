#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/utils/Reflection/Reflection.hpp>

namespace abyss::Adv::CodeZeroDemo
{
    class SignalCtrl : public IComponent
    {
    public:
        [[REFLECTION(RequestAppear)]]
        static void RequestAppear(AdvObj* pTalk);
        [[REFLECTION(IsAppearEnd)]]
        static bool IsAppearEnd(AdvObj* pTalk);

        [[REFLECTION(RequestPrepareBattle)]]
        static void RequestPrepareBattle(AdvObj* pTalk);

        [[REFLECTION(RequestBattleStart)]]
        static void RequestBattleStart(AdvObj* pTalk);
        [[REFLECTION(IsBattleEnd)]]
        static bool IsBattleEnd(AdvObj* pTalk);

        [[REFLECTION(RequestDead)]]
        static void RequestDead(AdvObj* pTalk);
        [[REFLECTION(IsDeadEnd)]]
        static bool IsDeadEnd(AdvObj* pTalk);
    public:
        SignalCtrl(AdvObj* pTalk);

        const AdvObj* getObj() const
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
        bool isRequestedPrepareBattle() const
        {
            return m_requestedPrepareBattle;
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
        void requestPrepareBattle()
        {
            m_requestedPrepareBattle = true;
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
        AdvObj* m_pTalk;

        bool m_requestedAppear = false;
        bool m_isAppearEnd = false;

        bool m_requestedPrepareBattle = false;
        bool m_isBattleStart = false;
        bool m_isBattleEnd = false;

        bool m_requestedDead = false;
        bool m_isDeadEnd = false;
    };
}

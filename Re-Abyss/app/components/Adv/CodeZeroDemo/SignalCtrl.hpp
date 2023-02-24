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
        static void RequestAppear(AdvObj* pObj);
        [[REFLECTION(IsAppearEnd)]]
        static bool IsAppearEnd(AdvObj* pObj);

        [[REFLECTION(RequestPrepareBattle)]]
        static void RequestPrepareBattle(AdvObj* pObj);

        [[REFLECTION(RequestBattleStart)]]
        static void RequestBattleStart(AdvObj* pObj);
        [[REFLECTION(IsBattleEnd)]]
        static bool IsBattleEnd(AdvObj* pObj);

        [[REFLECTION(RequestDead)]]
        static void RequestDead(AdvObj* pObj);
        [[REFLECTION(IsDeadEnd)]]
        static bool IsDeadEnd(AdvObj* pObj);
    public:
        SignalCtrl(AdvObj* pObj);

        const AdvObj* getObj() const
        {
            return m_pObj;
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
        AdvObj* m_pObj;

        bool m_requestedAppear = false;
        bool m_isAppearEnd = false;

        bool m_requestedPrepareBattle = false;
        bool m_isBattleStart = false;
        bool m_isBattleEnd = false;

        bool m_requestedDead = false;
        bool m_isDeadEnd = false;
    };
}

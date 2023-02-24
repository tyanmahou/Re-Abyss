#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/utils/Reflection/Reflection.hpp>

namespace abyss::Adv::RoomGarder
{
    class SignalCtrl : public IComponent
    {
    public:
        [[REFLECTION(IsAppearEnd)]]
        static bool IsAppearEnd(AdvObj* pTalk);

        [[REFLECTION(RequestBattleStart)]]
        static void RequestBattleStart(AdvObj* pTalk);
        [[REFLECTION(IsBattleEnd)]]
        static bool IsBattleEnd(AdvObj* pTalk);

        [[REFLECTION(IsDeadEnd)]]
        static bool IsDeadEnd(AdvObj* pTalk);
    public:
        SignalCtrl(AdvObj* pTalk);

        const AdvObj* getObj() const
        {
            return m_pTalk;
        }
        void requestAppearEnd()
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
        void requestDeadEnd()
        {
            m_isDeadEnd = true;
        }
    private:
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
        bool isDeadEnd() const
        {
            return m_isDeadEnd;
        }
    private:
        AdvObj* m_pTalk;

        bool m_isAppearEnd = false;

        bool m_isBattleStart = false;
        bool m_isBattleEnd = false;

        bool m_isDeadEnd = false;
    };
}

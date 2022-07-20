#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/utils/Reflection/Reflection.hpp>

namespace abyss::Novel::RoomGarder
{
    class SignalCtrl : public IComponent
    {
    public:
        [[REFLECTION(IsBattleStart)]]
        static bool IsBattleStart(TalkObj* pTalk);
        [[REFLECTION(IsBattleEnd)]]
        static bool IsBattleEnd(TalkObj* pTalk);
        [[REFLECTION(IsRoomGarderEnd)]]
        static bool IsRoomGarderEnd(TalkObj* pTalk);
    public:
        SignalCtrl(TalkObj* pTalk);

        const TalkObj* getObj() const
        {
            return m_pTalk;
        }
        void requestBattleStart()
        {
            m_isBattleStart = true;
        }
        void requestBattleEnd()
        {
            m_isBattleEnd = true;
        }
        void requestRoomGarderEnd()
        {
            m_isRoomGarderEnd = true;
        }
    private:
        bool isBattleStart() const
        {
            return m_isBattleStart;
        }
        bool isBattleEnd() const
        {
            return m_isBattleEnd;
        }
        bool isRoomGarderEnd() const
        {
            return m_isRoomGarderEnd;
        }
    private:
        TalkObj* m_pTalk;

        bool m_isBattleStart = false;
        bool m_isBattleEnd = false;
        bool m_isRoomGarderEnd = false;
    };
}

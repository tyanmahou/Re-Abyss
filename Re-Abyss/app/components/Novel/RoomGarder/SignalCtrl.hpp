#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/utils/Reflection/Reflection.hpp>

namespace abyss::Novel::RoomGarder
{
    class SignalCtrl : public IComponent
    {
    public:
        [[REFLECTION(IsRoomGarderStart)]]
        static bool IsRoomGarderStart(TalkObj* pTalk);
        [[REFLECTION(IsRoomGarderEnd)]]
        static bool IsRoomGarderEnd(TalkObj* pTalk);
    public:
        SignalCtrl(TalkObj* pTalk);

        const TalkObj* getObj() const
        {
            return m_pTalk;
        }
        void requestRoomGarderStart()
        {
            m_isRoomGarderStart = true;
        }
        void requestRoomGarderEnd()
        {
            m_isRoomGarderEnd = true;
        }
    private:
        bool isRoomGarderStart() const
        {
            return m_isRoomGarderStart;
        }
        bool isRoomGarderEnd() const
        {
            return m_isRoomGarderEnd;
        }
    private:
        TalkObj* m_pTalk;

        bool m_isRoomGarderStart = false;
        bool m_isRoomGarderEnd = false;
    };
}

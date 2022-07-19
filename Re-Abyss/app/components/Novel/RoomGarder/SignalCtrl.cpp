#include <abyss/components/Novel/RoomGarder/SignalCtrl.hpp>
#include <abyss/modules/Novel/base/TalkObj.hpp>

namespace abyss::Novel::RoomGarder
{
	SignalCtrl::SignalCtrl(TalkObj* pTalk) :
		m_pTalk(pTalk)
	{}
    bool SignalCtrl::IsRoomGarderStart(TalkObj* pTalk)
    {
        return pTalk->find<SignalCtrl>()->isRoomGarderStart();
    }
	bool SignalCtrl::IsRoomGarderEnd(TalkObj* pTalk)
	{
		return pTalk->find<SignalCtrl>()->isRoomGarderEnd();
	}
}

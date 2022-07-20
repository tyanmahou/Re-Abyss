#include <abyss/components/Novel/RoomGarder/SignalCtrl.hpp>
#include <abyss/modules/Novel/base/TalkObj.hpp>

namespace abyss::Novel::RoomGarder
{
	SignalCtrl::SignalCtrl(TalkObj* pTalk) :
		m_pTalk(pTalk)
	{}
    bool SignalCtrl::IsBattleStart(TalkObj* pTalk)
    {
        return pTalk->find<SignalCtrl>()->isBattleStart();
    }
	bool SignalCtrl::IsBattleEnd(TalkObj* pTalk)
	{
		return pTalk->find<SignalCtrl>()->isBattleEnd();
	}
	bool SignalCtrl::IsRoomGarderEnd(TalkObj* pTalk)
	{
		return pTalk->find<SignalCtrl>()->isRoomGarderEnd();
	}
}

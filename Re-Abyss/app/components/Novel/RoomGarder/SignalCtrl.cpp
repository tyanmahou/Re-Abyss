#include <abyss/components/Novel/RoomGarder/SignalCtrl.hpp>
#include <abyss/modules/Novel/base/TalkObj.hpp>

namespace abyss::Novel::RoomGarder
{
	SignalCtrl::SignalCtrl(TalkObj* pTalk) :
		m_pTalk(pTalk)
	{}
    bool SignalCtrl::IsAppearEnd(TalkObj* pTalk)
    {
        return pTalk->find<SignalCtrl>()->isAppearEnd();
    }
    void SignalCtrl::RequestBattleStart(TalkObj* pTalk)
    {
        pTalk->find<SignalCtrl>()->requestBattleStart();
    }
	bool SignalCtrl::IsBattleEnd(TalkObj* pTalk)
	{
		return pTalk->find<SignalCtrl>()->isBattleEnd();
	}
    bool SignalCtrl::IsDeadEnd(TalkObj* pTalk)
    {
        return pTalk->find<SignalCtrl>()->isDeadEnd();
    }
}

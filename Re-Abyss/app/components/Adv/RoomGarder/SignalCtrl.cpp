#include <abyss/components/Adv/RoomGarder/SignalCtrl.hpp>
#include <abyss/modules/Adv/base/AdvObj.hpp>

namespace abyss::Adv::RoomGarder
{
	SignalCtrl::SignalCtrl(AdvObj* pTalk) :
		m_pTalk(pTalk)
	{}
    bool SignalCtrl::IsAppearEnd(AdvObj* pTalk)
    {
        return pTalk->find<SignalCtrl>()->isAppearEnd();
    }
    void SignalCtrl::RequestBattleStart(AdvObj* pTalk)
    {
        pTalk->find<SignalCtrl>()->requestBattleStart();
    }
	bool SignalCtrl::IsBattleEnd(AdvObj* pTalk)
	{
		return pTalk->find<SignalCtrl>()->isBattleEnd();
	}
    bool SignalCtrl::IsDeadEnd(AdvObj* pTalk)
    {
        return pTalk->find<SignalCtrl>()->isDeadEnd();
    }
}

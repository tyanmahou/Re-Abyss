#include <abyss/components/Adv/RoomGarder/SignalCtrl.hpp>
#include <abyss/modules/Adv/base/AdvObj.hpp>

namespace abyss::Adv::RoomGarder
{
	SignalCtrl::SignalCtrl(AdvObj* pObj) :
		m_pObj(pObj)
	{}
    bool SignalCtrl::IsAppearEnd(AdvObj* pObj)
    {
        return pObj->find<SignalCtrl>()->isAppearEnd();
    }
    void SignalCtrl::RequestBattleStart(AdvObj* pObj)
    {
        pObj->find<SignalCtrl>()->requestBattleStart();
    }
	bool SignalCtrl::IsBattleEnd(AdvObj* pObj)
	{
		return pObj->find<SignalCtrl>()->isBattleEnd();
	}
    bool SignalCtrl::IsDeadEnd(AdvObj* pObj)
    {
        return pObj->find<SignalCtrl>()->isDeadEnd();
    }
}

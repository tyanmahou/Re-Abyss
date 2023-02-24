#include <abyss/components/Adv/CodeZeroDemo/SignalCtrl.hpp>
#include <abyss/modules/Adv/base/AdvObj.hpp>

namespace abyss::Adv::CodeZeroDemo
{
	SignalCtrl::SignalCtrl(AdvObj* pObj) :
		m_pObj(pObj)
	{}
	void SignalCtrl::RequestAppear(AdvObj* pObj)
	{
		pObj->find<SignalCtrl>()->requestAppear();
	}
	bool SignalCtrl::IsAppearEnd(AdvObj* pObj)
	{
		return pObj->find<SignalCtrl>()->isAppearEnd();
	}
    void SignalCtrl::RequestPrepareBattle(AdvObj* pObj)
    {
        pObj->find<SignalCtrl>()->requestPrepareBattle();
    }
    void SignalCtrl::RequestBattleStart(AdvObj* pObj)
    {
        pObj->find<SignalCtrl>()->requestBattleStart();
    }
    bool SignalCtrl::IsBattleEnd(AdvObj* pObj)
    {
        return pObj->find<SignalCtrl>()->isBattleEnd();
    }
    void SignalCtrl::RequestDead(AdvObj* pObj)
    {
        pObj->find<SignalCtrl>()->requestDead();
    }
    bool SignalCtrl::IsDeadEnd(AdvObj* pObj)
    {
        return pObj->find<SignalCtrl>()->isDeadEnd();
    }
}

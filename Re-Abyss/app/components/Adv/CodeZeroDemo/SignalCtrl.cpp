#include <abyss/components/Adv/CodeZeroDemo/SignalCtrl.hpp>
#include <abyss/modules/Adv/base/AdvObj.hpp>

namespace abyss::Adv::CodeZeroDemo
{
	SignalCtrl::SignalCtrl(AdvObj* pTalk) :
		m_pTalk(pTalk)
	{}
	void SignalCtrl::RequestAppear(AdvObj* pTalk)
	{
		pTalk->find<SignalCtrl>()->requestAppear();
	}
	bool SignalCtrl::IsAppearEnd(AdvObj* pTalk)
	{
		return pTalk->find<SignalCtrl>()->isAppearEnd();
	}
    void SignalCtrl::RequestPrepareBattle(AdvObj* pTalk)
    {
        pTalk->find<SignalCtrl>()->requestPrepareBattle();
    }
    void SignalCtrl::RequestBattleStart(AdvObj* pTalk)
    {
        pTalk->find<SignalCtrl>()->requestBattleStart();
    }
    bool SignalCtrl::IsBattleEnd(AdvObj* pTalk)
    {
        return pTalk->find<SignalCtrl>()->isBattleEnd();
    }
    void SignalCtrl::RequestDead(AdvObj* pTalk)
    {
        pTalk->find<SignalCtrl>()->requestDead();
    }
    bool SignalCtrl::IsDeadEnd(AdvObj* pTalk)
    {
        return pTalk->find<SignalCtrl>()->isDeadEnd();
    }
}

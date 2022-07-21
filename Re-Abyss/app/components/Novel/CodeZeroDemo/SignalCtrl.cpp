#include <abyss/components/Novel/CodeZeroDemo/SignalCtrl.hpp>
#include <abyss/modules/Novel/base/TalkObj.hpp>

namespace abyss::Novel::CodeZeroDemo
{
	SignalCtrl::SignalCtrl(TalkObj* pTalk) :
		m_pTalk(pTalk)
	{}
	void SignalCtrl::RequestAppear(TalkObj* pTalk)
	{
		pTalk->find<SignalCtrl>()->requestAppear();
	}
	bool SignalCtrl::IsAppearEnd(TalkObj* pTalk)
	{
		return pTalk->find<SignalCtrl>()->isAppearEnd();
	}
    bool SignalCtrl::IsBattleEnd(TalkObj* pTalk)
    {
        return pTalk->find<SignalCtrl>()->isBattleEnd();
    }
    void SignalCtrl::RequestDead(TalkObj* pTalk)
    {
        pTalk->find<SignalCtrl>()->requestDead();
    }
    bool SignalCtrl::IsDeadEnd(TalkObj* pTalk)
    {
        return pTalk->find<SignalCtrl>()->isDeadEnd();
    }
}

#include <abyss/components/Novel/BossTalk0_1/SignalCtrl.hpp>
#include <abyss/modules/Novel/base/TalkObj.hpp>

namespace abyss::Novel::BossTalk0_1
{
	void SignalCtrl::RequestDead(TalkObj* pTalk)
	{
		pTalk->find<SignalCtrl>()->requestDead();
	}
	bool SignalCtrl::IsDeadEnd(TalkObj* pTalk)
	{
		return pTalk->find<SignalCtrl>()->isDeadEnd();
	}
	SignalCtrl::SignalCtrl(TalkObj* pTalk) :
		m_pTalk(pTalk)
	{}
}

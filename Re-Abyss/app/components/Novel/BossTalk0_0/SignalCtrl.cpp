#include <abyss/components/Novel/BossTalk0_0/SignalCtrl.hpp>
#include <abyss/modules/Novel/base/TalkObj.hpp>

namespace abyss::Novel::BossTalk0_0
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
}

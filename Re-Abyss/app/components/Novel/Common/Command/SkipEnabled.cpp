#include <abyss/components/Novel/Common/Command/SkipEnabled.hpp>
#include <abyss/components/Novel/base/SkipCtrl.hpp>
#include <abyss/modules/Novel/base/TalkObj.hpp>

namespace abyss::Novel
{
	SkipEnabled::SkipEnabled(TalkObj* pTalk, bool isEnabled):
		m_pTalk(pTalk),
		m_isEnabled(isEnabled)
	{}
	void SkipEnabled::onStart()
	{
		if (auto skipCtrl = m_pTalk->find<SkipCtrl>()) {
			skipCtrl->setIsEnabled(m_isEnabled);
		}
	}
	Coro::Task<> SkipEnabled::onCommand()
	{
		co_return;
	}
}

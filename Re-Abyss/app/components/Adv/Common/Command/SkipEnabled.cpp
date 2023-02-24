#include <abyss/components/Adv/Common/Command/SkipEnabled.hpp>
#include <abyss/modules/Adv/base/SkipCtrl.hpp>
#include <abyss/modules/Adv/base/AdvObj.hpp>

namespace abyss::Adv
{
	SkipEnabled::SkipEnabled(AdvObj* pObj, bool isEnabled):
		m_pObj(pObj),
		m_isEnabled(isEnabled)
	{}
	void SkipEnabled::onStart()
	{
		if (auto skipCtrl = m_pObj->find<SkipCtrl>()) {
			skipCtrl->setIsEnabled(m_isEnabled);
		}
	}
	Coro::Fiber<> SkipEnabled::onCommand()
	{
		co_return;
	}
}

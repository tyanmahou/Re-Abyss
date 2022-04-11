#include <abyss/components/Novel/base/SkipCtrl.hpp>
#include <abyss/commons/InputManager/InputManager.hpp>

namespace abyss::Novel
{
	SkipCtrl::SkipCtrl(TalkObj* pTalk):
		m_pTalk(pTalk)
	{
	}
	SkipCtrl& SkipCtrl::registCallback(const std::function<void()>& callback)
	{
		m_callbacks.push_back(callback);
		return *this;
	}
	bool SkipCtrl::isSkip() const
	{
		if (!m_isEnabled) {
			return false;
		}
		return InputManager::Start.down();
	}
	void SkipCtrl::onSkip()
	{
		for (auto&& callback : m_callbacks) {
			if (callback) {
				callback();
			}
		}
		m_callbacks.clear();
	}
}

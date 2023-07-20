#include <abyss/utils/DebugMenu/Button.hpp>
#include <Siv3D.hpp>

namespace abyss::DebugMenu
{
	Button::Button(
		const s3d::String& key,
		const std::function<void()>& callback
	):Button(key, key, callback)
	{
	}
	Button::Button(
		const s3d::String& key,
		const s3d::String& label, 
		const std::function<void()>& callback
	):
		m_key(key),
		m_label(label),
		m_callback(callback)
	{
	}
	void Button::onFoucsUpdate(const IInputController* input)
	{
		if (input->decide()) {
			if (m_callback) {
				m_callback();
			}
		}
	}
}

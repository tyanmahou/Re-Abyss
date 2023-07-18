#include <abyss/utils/DebugMenu/BoolItem.hpp>
#include <Siv3D.hpp>

namespace abyss::DebugMenu
{
	BoolItem::BoolItem(
		const s3d::String& key,
		const s3d::String& label,
		bool initValue,
		const std::function<void(bool)>& callback
	) :
		m_key(key),
		m_label(label),
        m_initValue(initValue),
		m_value(initValue),
		m_callback(callback)
	{
	}

	void BoolItem::onFoucsUpdate()
	{
		if (KeyZ.down()) {
            this->setValue(!m_value);
		}
	}
	void BoolItem::reset()
	{
        this->setValue(m_initValue);
    }
    void BoolItem::setValue(bool value)
    {
        m_value = value;
        if (m_callback) {
            m_callback(m_value);
        }
    }
}

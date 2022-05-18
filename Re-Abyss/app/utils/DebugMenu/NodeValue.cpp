#include <abyss/utils/DebugMenu/NodeValue.hpp>

namespace abyss::DebugMenu
{
	NodeValue::NodeValue(bool value):
		m_value(value)
	{}
	NodeValue::NodeValue(size_t value) :
		m_value(value)
	{}
	bool NodeValue::toBool() const
	{
		return std::get<bool>(m_value);
	}
}


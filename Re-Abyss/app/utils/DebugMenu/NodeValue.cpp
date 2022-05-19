#include <abyss/utils/DebugMenu/NodeValue.hpp>

namespace abyss::DebugMenu
{
	NodeValue::NodeValue(s3d::None_t):
		m_value(s3d::none)
	{
	}
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


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
	NodeValue::NodeValue(const std::pair<size_t, s3d::StringView>& value) :
		m_value(value)
	{}
	bool NodeValue::toBool() const
	{
		return std::get<bool>(m_value);
	}
	std::pair<size_t, s3d::StringView> NodeValue::toIndexedString() const
	{
		return std::get<std::pair<size_t, s3d::StringView>>(m_value);
	}
	s3d::Optional<std::pair<size_t, s3d::StringView>> NodeValue::toIndexedStringOpt() const
	{
		if (std::holds_alternative<std::pair<size_t, s3d::StringView>>(m_value)) {
			return this->toIndexedString();
		}
		return s3d::none;
	}
}


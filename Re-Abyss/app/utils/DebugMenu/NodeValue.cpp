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
	bool NodeValue::isBool() const
	{
		return std::holds_alternative<bool>(m_value);
	}
	bool NodeValue::toBool() const
	{
		return this->toBoolOpt().value_or(false);
	}
	s3d::Optional<bool> NodeValue::toBoolOpt() const
	{
		if (std::holds_alternative<bool>(m_value)) {
			return std::get<bool>(m_value);
		}
		return s3d::none;
	}
	bool NodeValue::isIndexed() const
	{
		return std::holds_alternative<std::pair<size_t, s3d::StringView>>(m_value);
	}
	std::pair<size_t, s3d::StringView> NodeValue::toIndexedString() const
	{
		return this->toIndexedStringOpt().value_or(std::pair<size_t, s3d::StringView>{0, U""});
	}
	s3d::Optional<std::pair<size_t, s3d::StringView>> NodeValue::toIndexedStringOpt() const
	{
		if (std::holds_alternative<std::pair<size_t, s3d::StringView>>(m_value)) {
			return std::get<std::pair<size_t, s3d::StringView>>(m_value);
		}
		return s3d::none;
	}
	size_t NodeValue::toIndex() const
	{
		return this->toIndexedString().first;
	}
}


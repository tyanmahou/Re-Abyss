#pragma once
#include <variant>

namespace abyss::DebugMenu
{
	class NodeValue
	{
	public:
		NodeValue() = default;

		NodeValue(bool value);
		NodeValue(size_t value);


		bool toBool() const;
	private:
		std::variant<bool, size_t> m_value;
	};
}
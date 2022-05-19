#pragma once
#include <variant>
#include <Siv3D/None.hpp>

namespace abyss::DebugMenu
{
	class NodeValue
	{
	public:
		NodeValue() = default;

		NodeValue(s3d::None_t);

		NodeValue(bool value);
		NodeValue(size_t value);


		bool toBool() const;
	private:
		std::variant<s3d::None_t, bool, size_t> m_value;
	};
}
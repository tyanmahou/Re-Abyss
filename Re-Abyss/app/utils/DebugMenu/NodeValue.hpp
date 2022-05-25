#pragma once
#include <variant>
#include <utility>
#include <Siv3D/Optional.hpp>
#include <Siv3D/StringView.hpp>

namespace abyss::DebugMenu
{
	class NodeValue
	{
	public:
		NodeValue() = default;

		NodeValue(s3d::None_t);

		NodeValue(bool value);
		NodeValue(const std::pair<size_t, s3d::StringView>& value);

		bool isBool() const;
		bool toBool() const;
		s3d::Optional<bool> toBoolOpt() const;

		std::pair<size_t, s3d::StringView> toIndexedString() const;
		s3d::Optional<std::pair<size_t, s3d::StringView>> toIndexedStringOpt() const;
		size_t toIndex() const;
	private:
		std::variant<
			s3d::None_t, 
			bool,
			std::pair<size_t, s3d::StringView>
		> m_value;
	};
}
#pragma once
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/StringView.hpp>
#include <Siv3D/Array.hpp>
#include <Siv3D/Optional.hpp>

namespace abyss::DebugMenu
{
	class ISkin
	{
	public:
		virtual ~ISkin() = default;

		virtual void draw(const s3d::Array<s3d::StringView>& labels, const s3d::Optional<size_t> selectIndex) const = 0;
	};
}
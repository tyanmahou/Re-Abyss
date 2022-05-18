#pragma once
#include <Siv3D/StringView.hpp>

namespace abyss::DebugMenu
{
	class IItem
	{
	public:
		virtual s3d::StringView key() const = 0;
		virtual s3d::StringView label() const = 0;

		virtual void onFoucsUpdate() = 0;
	};
}
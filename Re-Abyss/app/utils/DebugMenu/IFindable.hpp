#pragma once
#include <Siv3D/StringView.hpp>

namespace abyss::DebugMenu
{
	class IFindable
	{
	public:
        virtual ~IFindable() = default;
		virtual s3d::StringView key() const = 0;
	};
}

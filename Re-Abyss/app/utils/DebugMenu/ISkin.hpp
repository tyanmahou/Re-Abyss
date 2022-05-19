#pragma once
#include <abyss/utils/DebugMenu/IFolder.hpp>

namespace abyss::DebugMenu
{
	class ISkin
	{
	public:
		virtual ~ISkin() = default;

		virtual void draw(const IFolder* pFolder) const = 0;
	};
}
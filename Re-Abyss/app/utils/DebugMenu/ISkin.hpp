#pragma once

namespace abyss::DebugMenu
{
	class RootFolder;

	class ISkin
	{
	public:
		virtual ~ISkin() = default;

		virtual void draw(const RootFolder* pRoot) const = 0;
	};
}
#pragma once
#include <abyss/utils/DebugMenu/Node.hpp>

namespace abyss::DebugMenu
{
	class MenuParser
	{
	public:
		static Node FromXML(s3d::FilePathView path, bool isRoot = false);
	};
}
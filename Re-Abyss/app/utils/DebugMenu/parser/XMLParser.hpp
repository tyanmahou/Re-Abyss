#pragma once
#include <abyss/utils/DebugMenu/Node.hpp>

namespace abyss::DebugMenu
{
	class XMLParser
	{
		static Node ParseFrom(s3d::FilePathView path, bool isRoot = false);
	};
}
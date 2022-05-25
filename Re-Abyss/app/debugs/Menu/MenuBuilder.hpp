#pragma once
#if ABYSS_DEBUG
#include <abyss/utils/Reflection/Reflection.hpp>
#include <abyss/utils/DebugMenu/Node.hpp>
#include <Siv3D/XMLReader.hpp>

namespace abyss::Debug
{
	struct MenuBuilder
	{
	public:
		[[REFLECTION(BuildSceneMenu)]]
		static DebugMenu::Node BuildSceneMenu(const s3d::XMLElement& xml);
	public:
		[[REFLECTION(ExecClearLog)]]
		static void ExecClearLog();

		[[REFLECTION(ExecSoundMute)]]
		static void ExecSoundMute(bool value);

		[[REFLECTION(ExecFPS)]]
		static void ExecFPS(s3d::StringView value);
	};
}

#endif
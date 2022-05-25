#pragma once
#if ABYSS_DEBUG
#include <abyss/utils/Reflection/Reflection.hpp>

namespace abyss::Debug
{
	struct MenuBuilder
	{
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
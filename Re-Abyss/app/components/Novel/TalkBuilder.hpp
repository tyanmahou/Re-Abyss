#pragma once
#include <abyss/commons/Fwd.hpp>
#include <Siv3D/Fwd.hpp>

namespace abyss::Novel
{
	struct TalkBuilder
	{
		static void Build(TalkObj* pTalk, const s3d::String& path);
	};
}
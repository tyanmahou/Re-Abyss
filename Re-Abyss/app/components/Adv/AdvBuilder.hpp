#pragma once
#include <abyss/commons/Fwd.hpp>
#include <Siv3D/Fwd.hpp>

namespace abyss::Adv
{
	struct AdvBuilder
	{
		static void Build(AdvObj* pTalk, const s3d::String& path);
	};
}

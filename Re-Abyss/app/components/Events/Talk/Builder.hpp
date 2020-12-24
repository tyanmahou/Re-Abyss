#pragma once
#include <abyss/commons/Fwd.hpp>
#include <Siv3D/Fwd.hpp>

namespace abyss::Event::Talk
{
	struct Builder
	{
		static void Build(IEvent* pEvent, const s3d::String& path);
	};
}

#pragma once
#include <abyss/types/Novel/CharaKind.hpp>
#include <abyss/types/Novel/Side.hpp>
#include <abyss/types/Novel/Name.hpp>
#include <abyss/types/Novel/Face.hpp>
#include <abyss/types/Novel/TagString.hpp>

namespace abyss::Novel
{
	struct SerifEntity
	{
		CharaKind kind{};
		Side side{};
		Face face;
		Name name;
		TagString message;
	};
}
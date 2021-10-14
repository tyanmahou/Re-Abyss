#pragma once
#include <abyss/types/Novel/ActorKind.hpp>
#include <abyss/types/Novel/Side.hpp>
#include <abyss/types/Novel/Name.hpp>
#include <abyss/types/Novel/Face.hpp>
#include <abyss/types/Novel/TagString.hpp>

namespace abyss::Novel
{
	struct SerifEntity
	{
		ActorKind kind{};
		Side side{};
		Face face;
		Name name;
		TagString message;
	};
}
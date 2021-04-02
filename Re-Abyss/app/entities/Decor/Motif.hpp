#pragma once

#include <variant>

namespace abyss::decor
{
	namespace Motif
	{
		enum class Common
		{
			Common,
		};

		enum class City
		{
			StreetLight,
		};

		enum class Gimmick
		{
			Door,
		};

		enum class Map
		{
			Common,
		};
	}

	using DecorType = std::variant<Motif::Common, Motif::City, Motif::Gimmick, Motif::Map>;
}
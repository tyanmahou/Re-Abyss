#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Decor
{
	namespace Map
	{
		class TileMapData;
	}
	class DecorTranslator
	{
	public:
		Ref<DecorObj> build(Decors& decor, const DecorEntity& entity) const;

		Ref<DecorObj> build(Decors& decor, const Map::TileMapData& tileMap) const;
	};
}

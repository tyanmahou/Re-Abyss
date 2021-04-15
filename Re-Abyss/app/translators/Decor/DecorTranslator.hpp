#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::decor
{
	namespace Map
	{
		class TileMapModel;
	}
	class DecorTranslator
	{
	public:
		Ref<DecorObj> build(Decor& decor, s3d::int32 order, const DecorEntity& entity) const;

		Ref<DecorObj> build(Decor& decor, s3d::int32 order, const Map::TileMapModel& tileMap) const;
	};
}

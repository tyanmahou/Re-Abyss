#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Decor
{
	namespace Map
	{
		class TileMapModel;
	}
	class DecorTranslator
	{
	public:
		Ref<DecorObj> build(Decors& decor, s3d::int32 order, const DecorEntity& entity) const;

		Ref<DecorObj> build(Decors& decor, s3d::int32 order, const Map::TileMapModel& tileMap) const;
	};
}

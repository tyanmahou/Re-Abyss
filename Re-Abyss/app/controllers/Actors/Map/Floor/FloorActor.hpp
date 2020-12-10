#pragma once
#include <abyss/controllers/Actors/Map/MapActor.hpp>

namespace abyss::Actor::Map::Floor
{
	class FloorActor : 
		public MapActor
	{
	public:
		FloorActor(ColDirection col, const s3d::Vec2& pos, const s3d::Vec2& size);

		bool accept(const ActVisitor& visitor) override;
	};
}
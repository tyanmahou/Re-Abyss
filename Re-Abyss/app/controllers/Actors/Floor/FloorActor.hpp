#pragma once
#include <abyss/controllers/Actors/Map/MapActor.hpp>

namespace abyss
{
	class FloorActor : public MapActor
	{
	public:
		FloorActor(ColDirection col, const s3d::Vec2& pos, const s3d::Vec2& size);

		void accept(const ActVisitor& visitor) override;
	};
}
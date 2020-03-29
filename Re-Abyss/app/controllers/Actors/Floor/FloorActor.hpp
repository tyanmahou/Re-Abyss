#pragma once
#include <abyss/controllers/Actors/Map/MapActor.hpp>
#include <abyss/controllers/Actors/base/Receiver.hpp>

namespace abyss
{
	class FloorActor : 
		public MapActor,
		public Receiver
	{
	public:
		FloorActor(ColDirection col, const s3d::Vec2& pos, const s3d::Vec2& size);

		bool accept(const ActVisitor& visitor) override;
	};
}
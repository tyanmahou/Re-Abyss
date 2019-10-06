#pragma once
#include "MapActor.hpp"
#include <application/types/Forward.hpp>

namespace abyss
{
	class FloorActor : public MapActor
	{
	public:
		FloorActor(ColDirection col, const s3d::Vec2& pos, const s3d::Vec2& size);

		void accept(const ActVisitor& visitor) override;
	};
}
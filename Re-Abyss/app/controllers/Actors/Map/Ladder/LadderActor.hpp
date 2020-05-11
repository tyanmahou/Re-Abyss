#pragma once
#include <abyss/controllers/Actors/Map/MapActor.hpp>

namespace abyss::Ladder
{
	class LadderActor : public MapActor
	{
	public:
		LadderActor(ColDirection col, const s3d::Vec2& pos, const s3d::Vec2& size);

		s3d::Line getCenterLine() const;
		bool isTop() const;

		bool accept(const ActVisitor& visitor) override;
	};
}
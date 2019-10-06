#pragma once
#include "MapActor.hpp"

namespace abyss
{
	class LadderActor : public MapActor
	{
	public:
		LadderActor(ColDirection col, const s3d::Vec2& pos, const s3d::Vec2& size);

		s3d::Line getCenterLine() const;
		bool isTop() const;

		void accept(const ActVisitor& visitor) override;
	};
}
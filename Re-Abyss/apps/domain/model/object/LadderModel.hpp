#pragma once
#include "MapModel.hpp"

#include <Siv3D/Fwd.hpp>

namespace abyss
{
	class LadderModel : public MapModel
	{
	public:
		LadderModel(ColDirection col, const s3d::Vec2& pos, const s3d::Vec2& size);

		s3d::Line getCenterLine() const;
		bool isTop() const;
	};
}
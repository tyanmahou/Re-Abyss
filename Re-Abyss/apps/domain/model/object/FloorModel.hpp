#pragma once
#include "MapModel.hpp"
#include "../../../application/types/Forward.hpp"
#include "../../../application/util/Collision.hpp"

#include <Siv3D/Fwd.hpp>

namespace abyss
{
	class FloorModel : public MapModel
	{
	public:
		FloorModel(ColDirection col, const s3d::Vec2& pos, const s3d::Vec2& size);
	};
}
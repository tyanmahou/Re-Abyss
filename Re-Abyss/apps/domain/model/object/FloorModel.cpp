#include "FloorModel.hpp"

#include <Siv3D.hpp>

namespace abyss
{
	FloorModel::FloorModel(ColDirection col, const s3d::Vec2& pos, const s3d::Vec2& size):
		MapModel(col, pos, size)
	{
		this->tag = L"floor";
	}


}
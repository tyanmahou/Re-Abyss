#include "FloorModel.hpp"
#include <domain/visitor/WorldVisitor.hpp>
#include <Siv3D.hpp>

namespace abyss
{
	FloorModel::FloorModel(ColDirection col, const s3d::Vec2& pos, const s3d::Vec2& size):
		MapModel(col, pos, size)
	{
		this->tag = U"floor";
	}

	void FloorModel::accept(const WorldVisitor& visitor)
	{
		visitor.visit(*this);
	}
}
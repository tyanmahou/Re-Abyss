#include "FloorActor.hpp"
#include <Siv3D/String.hpp>

namespace abyss
{
	FloorActor::FloorActor(ColDirection col, const s3d::Vec2& pos, const s3d::Vec2& size):
		MapActor(col, pos, size)
	{
		this->tag = U"floor";
	}

	bool FloorActor::accept(const ActVisitor& visitor)
	{
		return visitor.visit(*this);
	}
}
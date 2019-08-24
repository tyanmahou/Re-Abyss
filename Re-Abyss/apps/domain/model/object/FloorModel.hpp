#pragma once
#include "WorldObject.hpp"
#include "../../../application/types/Forward.hpp"
#include "../../../application/util/Collision.hpp"

#include <Siv3D/Fwd.hpp>

namespace abyss
{
	class FloorModel : public WorldObject
	{
	private:
		ColDirection m_col;
		s3d::Vec2 m_pos;
		s3d::Vec2 m_size;

	public:
		FloorModel(ColDirection col, const s3d::Vec2& pos, const s3d::Vec2& size);
		s3d::Shape getCollider() const override;

		s3d::RectF region() const;

		ColDirection getCol() const;
	};
}
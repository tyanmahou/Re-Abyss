#pragma once
#include "WorldObject.hpp"
#include "../../../application/util/Collision.hpp"

namespace abyss
{
	class MapModel :public WorldObject
	{
	protected:
		ColDirection m_col;
		s3d::Vec2 m_pos;
		s3d::Vec2 m_size;

	public:
		MapModel(ColDirection col, const s3d::Vec2& pos, const s3d::Vec2& size);

		const s3d::Vec2& getPos() const;
		ColDirection getCol() const;
	};
}
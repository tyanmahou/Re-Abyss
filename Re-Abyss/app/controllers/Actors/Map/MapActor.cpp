#include "MapActor.hpp"
#include <abyss/commons/LayerGroup.hpp>

namespace abyss
{
	MapActor::MapActor(ColDirection col, const s3d::Vec2& pos, const s3d::Vec2& size) :
		m_col(col),
		m_pos(pos),
		m_size(size)
	{
		this->layer = LayerGroup::Map;
	}

	const s3d::Vec2& MapActor::getPos() const
	{
		return m_pos;
	}

	ColDirection MapActor::getCol() const
	{
		return m_col;
	}

	s3d::RectF MapActor::region() const
	{
		return s3d::RectF{ m_pos - m_size / 2, m_size };
	}

	CShape MapActor::getCollider() const
	{
		return this->region();
	}
	bool MapActor::accept(const ActVisitor& visitor)
	{
		return visitor.visit(*this);
	}
    MapColInfo MapActor::getMapColInfo() const
    {
		return {
			.region = this->region(),
			.col = m_col
		};
    }
}
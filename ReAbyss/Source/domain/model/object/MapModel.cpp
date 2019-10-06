#include "MapModel.hpp"
#include <domain/visitor/WorldVisitor.hpp>

namespace abyss
{
	MapModel::MapModel(ColDirection col, const s3d::Vec2& pos, const s3d::Vec2& size) :
		m_col(col),
		m_pos(pos),
		m_size(size)
	{}

	const s3d::Vec2& MapModel::getPos() const
	{
		return m_pos;
	}

	ColDirection MapModel::getCol() const
	{
		return m_col;
	}

	s3d::RectF MapModel::region() const
	{
		return s3d::RectF{ m_pos - m_size / 2, m_size };
	}

	CShape MapModel::getCollider() const
	{
		return this->region();
	}
	void MapModel::accept(const WorldVisitor& visitor)
	{
		visitor.visit(*this);
	}
}
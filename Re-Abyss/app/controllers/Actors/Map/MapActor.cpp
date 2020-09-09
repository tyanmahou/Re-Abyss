#include "MapActor.hpp"
#include <abyss/components/Actors/Map/MapParam.hpp>
#include <abyss/components/Actors/Commons/Terrain.hpp>
#include <abyss/types/CShape.hpp>

namespace abyss::Actor::Map
{
	MapActor::MapActor(ColDirection col, const s3d::Vec2& pos, const s3d::Vec2& size) :
		m_col(col)
	{
		{
			m_mapParam = this->attach<MapParam>(pos, size);
		}
		// 地形
		{
			this->attach<Terrain>(this)
				->setMapColInfo(this->getMapColInfo());
		}
	}

	const s3d::Vec2& MapActor::getPos() const
	{
		return m_mapParam->getPos();
	}

	const s3d::Vec2& MapActor::getSize() const
	{
		return m_mapParam->getSize();
	}

	ColDirection MapActor::getCol() const
	{
		return m_col;
	}

	s3d::RectF MapActor::region() const
	{
		return m_mapParam->region();
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
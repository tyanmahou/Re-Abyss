#include "MapActor.hpp"
#include <abyss/commons/LayerGroup.hpp>
#include <abyss/models/Actors/Map/ColliderModel.hpp>
namespace abyss::Map
{
	MapActor::MapActor(ColDirection col, const s3d::Vec2& pos, const s3d::Vec2& size) :
		m_col(col)
	{
		layer = LayerGroup::Map;
		{
			auto collider = std::make_shared<ColliderModel>(this, pos, size);
			collider->setLayer(LayerGroup::Map);
			this->addComponent(collider);
			m_collider = collider;
		}

	}

	const s3d::Vec2& MapActor::getPos() const
	{
		return m_collider->getPos();
	}

	const s3d::Vec2& MapActor::getSize() const
	{
		return m_collider->getSize();
	}

	ColDirection MapActor::getCol() const
	{
		return m_col;
	}

	s3d::RectF MapActor::region() const
	{
		return m_collider->region();
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
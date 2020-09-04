#include "FloorActor.hpp"
#include <Siv3D/String.hpp>
#include <abyss/models/Collision/LayerGroup.hpp>
#include <abyss/models/Actors/Commons/CustomColliderModel.hpp>

namespace abyss::Actor::Map::Floor
{
	FloorActor::FloorActor(ColDirection col, const s3d::Vec2& pos, const s3d::Vec2& size):
		MapActor(col, pos, size)
	{
		{
			auto collider = this->attach<CustomColliderModel>(this);
			collider->setColFunc([this] {
				return this->getCollider();
			});
			collider->setLayer(LayerGroup::Map);
		}
	}

	bool FloorActor::accept(const ActVisitor& visitor)
	{
		return visitor.visit(*this);
	}
}
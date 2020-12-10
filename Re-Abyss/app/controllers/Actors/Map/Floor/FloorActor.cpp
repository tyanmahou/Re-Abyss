#include "FloorActor.hpp"
#include <Siv3D/String.hpp>
#include <abyss/models/Collision/LayerGroup.hpp>
#include <abyss/components/Actors/Commons/ReceiverData.hpp>
#include <abyss/components/Actors/Commons/CustomCollider.hpp>

namespace abyss::Actor::Map::Floor
{
	FloorActor::FloorActor(ColDirection col, const s3d::Vec2& pos, const s3d::Vec2& size):
		MapActor(col, pos, size)
	{
		m_tag = Tag::Floor{};
		{
			auto collider = this->attach<CustomCollider>(this);
			collider->setColFunc([this] {
				return this->getCollider();
			});
			collider->setLayer(LayerGroup::Map);
		}
		{
			this->attach<ReceiverData>();
		}
	}

	bool FloorActor::accept(const ActVisitor& visitor)
	{
		return visitor.visit(*this);
	}
}
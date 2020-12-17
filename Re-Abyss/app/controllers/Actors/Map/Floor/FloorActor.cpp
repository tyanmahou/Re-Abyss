#include "FloorActor.hpp"
#include <Siv3D/String.hpp>
#include <abyss/models/Collision/LayerGroup.hpp>
#include <abyss/components/Actors/Commons/ReceiverData.hpp>

namespace abyss::Actor::Map::Floor
{
	FloorActor::FloorActor(ColDirection col, const s3d::Vec2& pos, const s3d::Vec2& size):
		MapActor(col, pos, size)
	{
		m_tag = Tag::Floor{};

		{
			this->attach<ReceiverData>();
		}
	}
}
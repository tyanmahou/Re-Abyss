#include <abyss/translators/Actor/Item/ItemTranslator.hpp>

#include <abyss/entities/Actor/Item/RecoveryEntity.hpp>

#include<abyss/components/Actor/Item/Recovery/Builder.hpp>
#include <abyss/modules/World/World.hpp>

namespace abyss::Actor::Item
{
	Ref<Actor::ActorObj> ItemTranslator::buildActor(World& world, const ItemEntity& entity)
	{
#define CASE_ITEM(type) case ItemType::##type : return world.create<type::Builder>(static_cast<const type##Entity&>(entity))

		switch (entity.type) {
			CASE_ITEM(Recovery);
		default:
			break;
		}
		return nullptr;
#undef CASE_ITEM
	}
}

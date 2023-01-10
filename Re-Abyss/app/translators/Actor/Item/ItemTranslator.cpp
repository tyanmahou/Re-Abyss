#include <abyss/translators/Actor/Item/ItemTranslator.hpp>

#include <abyss/modules/Actor/Actors.hpp>
#include <abyss/entities/Actor/Item/ItemEntity.hpp>
#include <abyss/utils/Reflection/Reflection.hpp>

namespace abyss::Actor::Item
{
	Ref<Actor::ActorObj> ItemTranslator::buildActor(Actors& actors, const ItemEntity& entity)
	{
        if (auto builder = Reflect<>::find<void(ActorObj*, const ItemEntity&)>(
            U"abyss::Actor::Item::BuilderFromEntity<{}>::Build"_fmt(static_cast<s3d::int32>(entity.type))
            )) {
            auto obj = actors.create();
            builder(obj.get(), entity);
            return obj;
        }
        return nullptr;
	}
}

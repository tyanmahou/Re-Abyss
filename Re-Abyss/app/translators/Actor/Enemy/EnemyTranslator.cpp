#include <abyss/translators/Actor/Enemy/EnemyTranslator.hpp>
#include <abyss/modules/Actor/Actors.hpp>
#include <abyss/utils/Reflection/Reflection.hpp>
#include <abyss/entities/Actor/Enemy/EnemyEntity.hpp>

namespace abyss::Actor::Enemy
{
    Ref<Actor::ActorObj> EnemyTranslator::buildActor(Actors& actors, const EnemyEntity& entity)
    {
        if (auto builder = Reflect<>::find<void(ActorObj*, const EnemyEntity&)>(
            U"abyss::Actor::Enemy::BuilderFromEntity<{}>::Build"_fmt(static_cast<s3d::int32>(entity.type))
            )) {
            auto obj = actors.create();
            builder(obj.get(), entity);
            return obj;
        }
        return nullptr;
    }
}

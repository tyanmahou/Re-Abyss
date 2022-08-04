#include <abyss/components/Actor/Enemy/Warrus/Builder.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Enemy/BuilderFromEntity.hpp>
#include <abyss/components/Actor/Enemy/CommonBuilder.hpp>

namespace abyss::Actor::Enemy::Warrus
{
    void Builder::Build([[maybe_unused]]ActorObj* pActor, [[maybe_unused]] const WarrusEntity& entity)
    {

    }
}

namespace abyss::Actor::Enemy
{
    template struct BuilderFromEntity<EnemyType::Warrus>;
    template<>
    void BuilderFromEntity<EnemyType::Warrus>::Build(ActorObj* pActor, const EnemyEntity& entity)
    {
        Warrus::Builder::Build(pActor, static_cast<const WarrusEntity&>(entity));
    }
}

#include <abyss/components/Actor/Enemy/BazookaKun/Builder.hpp>

#include <abyss/components/Actor/Enemy/BuilderFromEntity.hpp>
#include <abyss/components/Actor/Enemy/CommonBuilder.hpp>

namespace abyss::Actor::Enemy::BazookaKun
{
    void Builder::Build(ActorObj* pActor, const BazookaKunEntity& entity)
    {

    }
}

namespace abyss::Actor::Enemy
{
    template struct BuilderFromEntity<EnemyType::BazookaKun>;
    template<>
    void BuilderFromEntity<EnemyType::BazookaKun>::Build(ActorObj* pActor, const EnemyEntity& entity)
    {
        BazookaKun::Builder::Build(pActor, static_cast<const BazookaKunEntity&>(entity));
    }
}

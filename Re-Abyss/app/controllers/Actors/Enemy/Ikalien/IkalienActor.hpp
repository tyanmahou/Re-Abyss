#pragma once
#include <abyss/controllers/Actors/Enemy/EnemyActor.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
    struct IkalienEntity;
}
namespace abyss::Actor::Enemy::Ikalien
{
    class IkalienActor :
        public EnemyActor
    {
    public:
        IkalienActor(const IkalienEntity& entity);

        CShape getCollider() const;
    };
}
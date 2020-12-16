#pragma once
#include <abyss/controllers/Actors/Enemy/EnemyActor.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
    struct CaptainTakoEntity;
}
namespace abyss::Actor::Enemy::CaptainTako
{
    class CaptainTakoActor :
        public EnemyActor
    {
    public:
        CaptainTakoActor(const CaptainTakoEntity& entity);
    };
}
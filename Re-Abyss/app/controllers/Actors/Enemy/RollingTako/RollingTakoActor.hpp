#pragma once
#include <abyss/controllers/Actors/Enemy/EnemyActor.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
    struct RollingTakoEntity;
}

namespace abyss::Actor::Enemy::RollingTako
{
    class RollingTakoActor :
        public EnemyActor
    {
    private:
        bool m_isWait;
    public:
        RollingTakoActor(const RollingTakoEntity& entity);

        bool accept(const ActVisitor& visitor) override;
    };
}
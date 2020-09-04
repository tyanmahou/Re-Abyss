#pragma once
#include <abyss/controllers/Actors/Enemy/EnemyActor.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
    struct LaunSharkEntity;
}
namespace abyss::Actor::LaunShark
{
    class LaunSharkActor :
        public EnemyActor
    {
    public:
        LaunSharkActor(const LaunSharkEntity& entity);

        bool accept(const ActVisitor& visitor) override;
    };
}
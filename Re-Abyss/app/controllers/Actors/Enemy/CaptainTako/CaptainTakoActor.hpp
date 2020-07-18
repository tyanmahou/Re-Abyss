#pragma once
#include <abyss/controllers/Actors/Enemy/EnemyActor.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
    struct CaptainTakoEntity;
}
namespace abyss::CaptainTako
{
    class CaptainTakoActor :
        public EnemyActor
    {
    public:
        CaptainTakoActor(const CaptainTakoEntity& entity);

        bool accept(const ActVisitor& visitor) override;
    };
}
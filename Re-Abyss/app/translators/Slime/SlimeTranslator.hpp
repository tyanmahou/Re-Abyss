#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/models/actors/Slime/SlimeActor.hpp>

namespace abyss
{
    class SlimeTranslator
    {
    public:
        static std::shared_ptr<SlimeActor> ToActorPtr(const EnemyEntity& entity);
        static SlimeViewModel ToViewModel(const SlimeActor& actor);
    };
}

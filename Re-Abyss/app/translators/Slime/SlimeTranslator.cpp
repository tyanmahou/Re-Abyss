#include "SlimeTranslator.hpp"

#include <abyss/entities/EnemyEntity.hpp>
#include <abyss/views/actors/Slime/SlimeView.hpp>

namespace abyss
{
    SlimeViewModel SlimeTranslator::ToViewModel(const SlimeActor& actor)
    {
        return SlimeViewModel{

        };
    }
    std::shared_ptr<SlimeActor> SlimeTranslator::ToActorPtr(const EnemyEntity& entity)
    {
        return std::make_shared<SlimeActor>(entity.pos);
    }
}

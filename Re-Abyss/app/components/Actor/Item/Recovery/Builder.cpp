#include "Builder.hpp"
#include <abyss/components/Actor/Item/CommonBuilder.hpp>
#include <abyss/entities/Actor/Item/RecoveryEntity.hpp>

namespace abyss::Actor::Item::Recovery
{
    void Builder::Build(ActorObj* pActor, const RecoveryEntity& entity)
    {
        CommonBuilder::Build(pActor, BuildOption{}
            .setInitPos(entity.pos)
        );
    }
}
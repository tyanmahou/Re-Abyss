#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Item
{
    class ItemTranslator
    {
    public:
        Ref<Actor::ActorObj> buildActor(Actors& actors, const ItemEntity& entity);
    };
}

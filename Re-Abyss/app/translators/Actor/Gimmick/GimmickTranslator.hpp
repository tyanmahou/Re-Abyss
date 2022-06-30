#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>

namespace abyss::Actor::Gimmick
{
    class GimmickTranslator
    {
    public:
        GimmickTranslator();

        Ref<Actor::ActorObj> buildActor(World& world, const GimmickEntity& entity);
    };
}

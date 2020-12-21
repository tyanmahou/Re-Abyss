#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Actors/base/IActor.hpp>

namespace abyss
{
    class GimmickTranslator
    {
        const Stage* m_pStage = nullptr;
    public:
        GimmickTranslator(const Stage* pStage);

        Ref<Actor::IActor> buildActor(World& world, const GimmickEntity& entity);
    };
}
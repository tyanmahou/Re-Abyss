#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>

namespace abyss::Actor::Gimmick
{
    class GimmickTranslator
    {
        const Stage* m_pStage = nullptr;
    public:
        GimmickTranslator(const Stage* pStage);

        Ref<Actor::ActorObj> buildActor(World& world, const GimmickEntity& entity);
    };
}
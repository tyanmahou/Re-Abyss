#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/controllers/Actors/base/IActor.hpp>

namespace abyss
{
    class GimmickTranslator
    {
        const Stage* m_pStage = nullptr;
    public:
        GimmickTranslator(const Stage* pStage);
        std::shared_ptr<IActor> toActorPtr(const GimmickEntity& entity);
    };
}
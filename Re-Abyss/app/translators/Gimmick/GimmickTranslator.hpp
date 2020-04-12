#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/controllers/Actors/base/IActor.hpp>

namespace abyss
{
    class GimmickTranslator
    {
        Stage* m_pStage = nullptr;
    public:
        GimmickTranslator(Stage* pStage);
        std::shared_ptr<IActor> toActorPtr(const GimmickEntity& entity);
    };
}
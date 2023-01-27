#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/entities/Decor/DecorEntity.hpp>
#include <abyss/utils/Reflection/Reflection.hpp>

namespace abyss::Decor
{
    template<DecorType::Motif Motif, auto Type>
    struct BuilderFromEntity
    {
        [[REFLECTION(Build)]]
        static void Build(DecorObj* pDecor, const DecorEntity& entity);
    };
}

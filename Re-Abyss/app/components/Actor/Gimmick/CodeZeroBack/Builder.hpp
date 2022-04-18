#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss::Actor::Gimmick
{
    struct CodeZeroBackEntity;
}
namespace abyss::Actor::Gimmick::CodeZeroBack
{
    struct Builder
    {
        static void Build(ActorObj* pActor, const CodeZeroBackEntity& entity);
    };
}
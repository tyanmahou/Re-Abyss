#pragma once
#include <concepts>
#include <Siv3D/Fwd.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss::Effect
{
    template<class T>
    concept DerviedFromSivEffect = std::derived_from<T, s3d::IEffect>;

    template<class Type, class... Args>
    concept EffectBuildy = requires(EffectObj* pObj, Args&&... args)
    {
        Type::Build(pObj, std::forward<Args>(args)...);
    };
}
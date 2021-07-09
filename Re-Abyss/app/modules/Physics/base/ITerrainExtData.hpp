#pragma once
#include <concepts>

namespace abyss::Physics
{
    struct ITerrainExtData
    {
        virtual ~ITerrainExtData() = default;
    };

    template<class T>
    concept TerrainExtended = std::derived_from<T, ITerrainExtData>;
}
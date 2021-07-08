#pragma once
#include <Siv3D/Array.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Physics
{
    class IContacter;
    class ITerrain;

    /// <summary>
    /// 衝突検出アルゴリズム
    /// </summary>
    class IDetectionAlgorithm
    {
    public:
        virtual ~IDetectionAlgorithm() = default;

        virtual void collisionAll(
            const s3d::Array<Ref<IContacter>>& contacters,
            const s3d::Array<Ref<ITerrain>>& terrains
        ) = 0;
    };
}
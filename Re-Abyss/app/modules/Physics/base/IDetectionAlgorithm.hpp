#pragma once
#include <memory>
#include <Siv3D/Array.hpp>

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
            const s3d::Array<std::shared_ptr<IContacter>>& contacters,
            const s3d::Array<std::shared_ptr<ITerrain>>& terrains
        ) = 0;
    };
}
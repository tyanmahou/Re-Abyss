#pragma once
#include <abyss/modules/Physics/base/IDetectionAlgorithm.hpp>

namespace abyss::Physics
{
    class SimpleDetection : public IDetectionAlgorithm
    {
    private:
        void collisionAll(
            const s3d::Array<std::shared_ptr<IContacter>>& contacters,
            const s3d::Array<std::shared_ptr<ITerrain>>& terrains
        );
    };
}
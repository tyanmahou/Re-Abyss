#pragma once
#include <abyss/modules/Physics/base/IDetectionAlgorithm.hpp>

namespace abyss::Physics
{
    class SimpleDetection : public IDetectionAlgorithm
    {
    private:
        void collisionAll(
            const s3d::Array<Ref<IDetector>>& detectors,
            const s3d::Array<Ref<ITerrain>>& terrains
        );
    };
}
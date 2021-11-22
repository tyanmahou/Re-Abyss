#pragma once
#include <abyss/modules/ColSys/base/IDetectionAlgorithm.hpp>

namespace abyss::ColSys
{
    class SimpleDetection final : public IDetectionAlgorithm
    {
    private:
        void collisionAll(const s3d::Array<std::shared_ptr<Branch>>& branchs) final;
    };
}
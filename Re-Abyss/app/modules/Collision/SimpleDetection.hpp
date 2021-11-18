#pragma once
#include <abyss/modules/Collision/base/IDetectionAlgorithm.hpp>

namespace abyss::Collision
{
    class SimpleDetection final : public IDetectionAlgorithm
    {
    private:
        void collisionAll(const s3d::Array<std::shared_ptr<INode>>& nodes) final;
    };
}
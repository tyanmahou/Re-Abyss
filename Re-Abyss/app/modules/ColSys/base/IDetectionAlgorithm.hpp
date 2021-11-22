#pragma once
#include <memory>
#include <Siv3D/Array.hpp>

namespace abyss::ColSys
{
    class Branch;

    /// <summary>
    /// 当たりアルゴリズム
    /// </summary>
    class IDetectionAlgorithm
    {
    public:
        virtual ~IDetectionAlgorithm() = default;

        virtual void collisionAll(const s3d::Array<std::shared_ptr<Branch>>& branchs) = 0;
    };
}
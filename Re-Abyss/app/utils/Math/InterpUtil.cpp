#include <abyss/utils/Math/InterpUtil.hpp>
#include <Siv3D.hpp>

namespace abyss
{
    double InterpUtil::DampRatio(double ratio, double dt, const Fps& baseFps)
    {
        return 1.0 - s3d::Pow(1.0 - ratio, baseFps.frame(dt));
    }
    s3d::Mat3x2 InterpUtil::Lerp(const Mat3x2& start, const Mat3x2& end, double t)
    {
        const float ft = static_cast<float>(t);
        return Mat3x2{
            s3d::Math::Lerp<float>(start._11, end._11, ft),
            s3d::Math::Lerp<float>(start._12, end._12, ft),
            s3d::Math::Lerp<float>(start._21, end._21, ft),
            s3d::Math::Lerp<float>(start._22, end._22, ft),
            s3d::Math::Lerp<float>(start._31, end._31, ft),
            s3d::Math::Lerp<float>(start._32, end._32, ft)
        };
    }
}

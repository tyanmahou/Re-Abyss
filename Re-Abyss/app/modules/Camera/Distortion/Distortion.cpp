#include "Distortion.hpp"
#include <abyss/utils/DistUtil/DistUtl.hpp>
#include <Siv3D.hpp>

namespace abyss
{
    void Distortion::clear()
    {
        m_drawer.clear();
    }

    void Distortion::addCircleFrame(const s3d::Circle& circle, double thickness, double power)
    {
        m_drawer.push_back([=]{
            DistUtil::DrawFrame(circle, thickness, power);
        });
    }
}

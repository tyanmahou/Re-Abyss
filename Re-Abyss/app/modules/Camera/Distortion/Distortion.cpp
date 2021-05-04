#include "Distortion.hpp"
#include <abyss/utils/DistUtil/DistUtl.hpp>
#include <Siv3D.hpp>

namespace abyss
{
    void Distortion::clear()
    {
        m_view.clear();
    }

    void Distortion::addCircleFrame(const s3d::Circle& circle, double thickness, double power)
    {
        m_view.addCircleFrame(circle, thickness, power);
    }
    s3d::ScopedCustomShader2D Distortion::start() const
    {
        return m_view.start();
    }
}

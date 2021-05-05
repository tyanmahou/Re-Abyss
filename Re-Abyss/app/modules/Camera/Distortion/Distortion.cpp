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
    void Distortion::addCircleFrame(const s3d::Circle& circle, double innerThickness, double outerThickness, double innerPower, double outerPower)
    {
        m_view.addCircleFrame(circle, innerThickness, outerThickness, innerPower, outerPower);
    }
    void Distortion::render() const
    {
        m_view.render();
    }
    s3d::ScopedCustomShader2D Distortion::start() const
    {
        return m_view.start();
    }
}

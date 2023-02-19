#include <abyss/modules/Distortion/Distortion.hpp>
#include <abyss/views/Distortion/DistUtl.hpp>
#include <Siv3D.hpp>

namespace abyss
{
    void Distortion::clear()
    {
        m_view.clear();
    }

    void Distortion::addCircle(const s3d::Circle& circle, double power)
    {
        m_view.addCircle(circle, power);
    }

    void Distortion::addCircle(const s3d::Circle & circle, double innerPower, double outerPower)
    {
        m_view.addCircle(circle, innerPower, outerPower);
    }

    void Distortion::addCircleFrame(const s3d::Circle& circle, double thickness, double power)
    {
        m_view.addCircleFrame(circle, thickness, power);
    }
    void Distortion::addCircleFrame(const s3d::Circle& circle, double innerThickness, double outerThickness, double innerPower, double outerPower)
    {
        m_view.addCircleFrame(circle, innerThickness, outerThickness, innerPower, outerPower);
    }
    void Distortion::addCircleFrameGiza(const s3d::Circle& circle, double innerThickness, double outerThickness, double innerSpread, double outerSpread, double innerPower, double outerPower)
    {
        m_view.addCircleFrameGiza(
            circle,
            innerThickness,
            outerThickness,
            innerSpread,
            outerSpread,
            innerPower,
            outerPower
        );
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

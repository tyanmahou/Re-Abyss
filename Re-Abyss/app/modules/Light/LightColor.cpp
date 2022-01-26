#include <abyss/modules/Light/LightColor.hpp>
#include <Siv3D.hpp>

namespace abyss
{
    constexpr double erpTime = 0.3;

    void LightColor::update(double dt)
    {
        if (m_erpTimer >= erpTime) {
            return;
        }

        m_erpTimer += dt;
        ColorF nextColor = m_nextColor.value_or(m_defaultColor);
        
        double rate0_1 = s3d::Saturate(m_erpTimer / erpTime);

        m_color.r = s3d::Math::Lerp(m_prevColor.r, nextColor.r, rate0_1);
        m_color.g = s3d::Math::Lerp(m_prevColor.g, nextColor.g, rate0_1);
        m_color.b = s3d::Math::Lerp(m_prevColor.b, nextColor.b, rate0_1);
        m_color.a = s3d::Math::Lerp(m_prevColor.a, nextColor.a, rate0_1);
    }
    void LightColor::initColor(const s3d::Optional<s3d::ColorF>& color)
    {
        auto initColor = color.value_or(m_defaultColor);
        m_prevColor = initColor;
        m_nextColor = initColor;
        m_color = initColor;
        m_erpTimer = erpTime;
    }
    void LightColor::setNextColor(const s3d::Optional<s3d::ColorF>& color)
    {
        m_prevColor = m_color;
        m_nextColor = color;
        m_erpTimer = 0.0;
    }

}

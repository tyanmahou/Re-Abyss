#pragma once
#include <Siv3D/ColorF.hpp>
#include <Siv3D/Optional.hpp>

namespace abyss
{
    /// <summary>
    /// ライトカラー
    /// </summary>
    class LightColor
    {
    public:
        void update(double dt);

        void initColor(const s3d::Optional<s3d::ColorF>& color);

        void setNextColor(const s3d::Optional<s3d::ColorF>& color);

        void setDefaultColor(const s3d::Color& color)
        {
            m_defaultColor = color;
        }

        const s3d::ColorF& getColor() const
        {
            return m_color;
        }
    private:
        double m_erpTimer = 0.0;
        s3d::ColorF m_color;
        s3d::ColorF m_prevColor;
        s3d::Optional<s3d::ColorF> m_nextColor;
        s3d::ColorF m_defaultColor;
    };
}
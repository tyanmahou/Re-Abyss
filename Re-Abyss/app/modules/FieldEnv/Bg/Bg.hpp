#pragma once
#include <Siv3D/Color.hpp>

namespace abyss::FieldEnv
{
    class Bg
    {
    public:
        Bg();

        void setColor(const s3d::ColorF& color)
        {
            m_bgColor = color;
        }
        const s3d::ColorF& getColor() const
        {
            return m_bgColor;
        }
        void draw(const s3d::RectF& screen) const;
    private:
        s3d::ColorF m_bgColor;
    };
}

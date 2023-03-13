#include <abyss/views/UI/Home/Top/ModeSelectLineVM.hpp>
#include <abyss/views/UI/Home/Top/ColorDef.hpp>

namespace abyss::UI::Home::Top
{
    void ModeSelectLineVM::draw() const
    {
        auto t2d = Transformer2D(s3d::Mat3x2::Rotate(-s3d::Math::QuarterPi, m_pos));
        // Line
        {
            const auto animeRate = s3d::Min(m_time, 0.3) / 0.3;
            Line(m_line0.begin, s3d::Math::Lerp(m_line0.begin, m_line0.end, animeRate))
                .moveBy(m_pos)
                .draw(ColorDef::Color1);
            Line(m_line1.begin, s3d::Math::Lerp(m_line1.begin, m_line1.end, animeRate))
                .moveBy(m_pos)
                .draw(ColorDef::Color1);
        }

        // Text
        {
            const auto animeRate = s3d::Min(m_time, 0.2) / 0.2;
            constexpr Vec2 baseSize{ 160, 160 };
            Vec2 size = baseSize * m_scale;

            const auto animOffs = s3d::Math::Lerp(Vec2{ -10, 0 }, Vec2{ 0, 0 }, animeRate);
            FontAsset(U"pm12b-20")(m_isLocked ? U"???" : m_text)
                .draw(m_pos - size / 2 + m_textOffset + animOffs, ColorF(ColorDef::Color1, animeRate));
        }
    }
}

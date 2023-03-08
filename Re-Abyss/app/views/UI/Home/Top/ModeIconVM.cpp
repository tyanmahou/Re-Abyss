#include <abyss/views/UI/Home/Top/ModeIconVM.hpp>

namespace
{
    constexpr Color color1(223, 228, 246);
    constexpr Color color2(110, 110, 170);
}
namespace abyss::UI::Home::Top
{
    void ModeIconVM::draw() const
    {
        const Color& mainColor = m_isReverseColor ? color2 : color1;
        const Color& subColor = m_isReverseColor ? color1 : color2;

        constexpr Vec2 baseSize{ 160, 160 };
        Vec2 size = baseSize * m_scale;
        RectF rect(m_pos - size / 2, size);
        // 下地
        {
            rect
                .rotatedAt(m_pos, s3d::Math::QuarterPi)
                .draw(mainColor)
                .drawFrame(5 * m_scale, 0, subColor)
                .scaledAt(m_pos, 0.8)
                .drawFrame(1, subColor);
        }
        // アイコン
        if (m_icon) {
            m_icon
                .scaled(m_iconScale)
                .drawAt(m_pos + m_iconOffset, subColor);
        }
        // テキスト
        if (m_font) {
            auto t2d = Transformer2D(s3d::Mat3x2::Rotate(-s3d::Math::QuarterPi, m_pos));
            m_font(m_text)
                .draw( rect.tl() + m_textOffset, color1);
        }
    }
}

#include <abyss/views/UI/Home/Top/ModeIconVM.hpp>
#include <abyss/views/UI/Home/Top/ModeIcon/IModeThumb.hpp>

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
        // サムネイル
        if (m_thumbnail) {
            if (m_isSelected) {
                m_thumbnail->drawSelected(m_pos, m_time, { mainColor, subColor });
            } else {
                m_thumbnail->drawUnselected(m_pos, m_time, { mainColor, subColor });
            }
        }
        // テキスト
        if (m_isSelected) {
            auto t2d = Transformer2D(s3d::Mat3x2::Rotate(-s3d::Math::QuarterPi, m_pos));
            FontAsset(U"pm12b-20")(m_text)
                .draw( rect.tl() + m_textOffset, color1);
        }
    }
}

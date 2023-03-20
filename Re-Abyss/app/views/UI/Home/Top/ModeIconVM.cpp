#include <abyss/views/UI/Home/Top/ModeIconVM.hpp>
#include <abyss/views/UI/Home/Top/ModeIcon/IModeThumb.hpp>
#include <abyss/views/UI/Home/Top/ColorDef.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss::UI::Home::Top
{
    ModeIconVM::ModeIconVM()
    {}

    void ModeIconVM::draw() const
    {
        const Color& mainColor = m_isReverseColor ? ColorDef::Color2 : ColorDef::Color1;
        const Color& subColor = m_isReverseColor ? ColorDef::Color1 : ColorDef::Color2;

        constexpr Vec2 baseSize{ 160, 160 };
        Vec2 size = baseSize * m_scale;

        // 選択時ぷにゅん
        constexpr double selectedPunyunTime = 0.2;
        if (m_isSelected && m_time <= selectedPunyunTime) {
            size *= s3d::Math::Lerp(1.1, 1.0, s3d::Min(m_time, selectedPunyunTime) / selectedPunyunTime);
        }
        const RectF rect(m_pos - size / 2, size);
        const auto rotatedRect = rect.rotatedAt(m_pos, s3d::Math::QuarterPi);
        // 下地
        {
            rotatedRect
                .draw(mainColor)
                .drawFrame(5 * m_scale, 0, subColor)
                .scaledAt(m_pos, 0.8)
                .drawFrame(1, subColor);
        }
        // サムネイル
        if (m_isLocked) {
            if (m_lockThumbnail) {
                if (m_isSelected) {
                    m_lockThumbnail->drawSelected(m_pos, m_time, { mainColor, subColor });
                } else {
                    m_lockThumbnail->drawUnselected(m_pos, m_time, { mainColor, subColor });
                }
            }
            {
                s3d::ScopedRenderStates2D scopedBlend(BlendState::Subtractive);
                rotatedRect.draw(ColorF(1, 0.5));
            }
        } else if (m_thumbnail) {
            if (m_isSelected) {
                m_thumbnail->drawSelected(m_pos, m_time, { mainColor, subColor });
            } else {
                m_thumbnail->drawUnselected(m_pos, m_time, { mainColor, subColor });
            }
        }
    }
}

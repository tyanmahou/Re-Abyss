#include "MessageVM.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/commons/FontName.hpp>

namespace abyss::UI::Serif
{
    MessageVM& MessageVM::setPos(const s3d::Vec2& pos)
    {
        m_pos = pos;
        return *this;
    }
    MessageVM& MessageVM::setCurrent(const String& current)
    {
        m_currentMessage = current;
        return *this;
    }
    MessageVM& MessageVM::setPrev(const String& prev)
    {
        m_prevMessage = prev;
        return *this;
    }
    MessageVM& MessageVM::setStrIndex(s3d::int32 strIndex)
    {
        m_strIndex = strIndex;
        return *this;
    }
    void MessageVM::draw() const
    {
        auto&& font = FontAsset(FontName::Serif);
        if (!m_prevMessage.isEmpty()) {
            const auto offset = EaseIn(Easing::Linear, static_cast<double>(m_strIndex) / 2.0) * 2;
            const auto alpha  = static_cast<uint32>(Max(0.0, 255.0 - offset * 50.0));

            // 一つ前の描画
            Vec2 pos = m_pos;
            Color color = Palette::White;
            for (const auto& [index, glyph] : Indexed(font.getGlyphs(m_prevMessage))) {
                if (glyph.codePoint == U'\n') {
                    pos.x = m_pos.x;
                    pos.y += font.height() + 4;
                    continue;
                }
                auto drawPos = pos + glyph.getOffset();
                drawPos.y -= offset;
                glyph.texture.draw(drawPos, color.setA(alpha));
                pos.x += glyph.xAdvance;
            }
        }
        {
            // 現在のテキスト描画
            Vec2 pos = m_pos;
            Color color = Palette::White;
            for (const auto& [index, glyph] : Indexed(font.getGlyphs(m_currentMessage))) {
                if (glyph.codePoint == U'\n') {
                    pos.x = m_pos.x;
                    pos.y += font.height() + 4;
                    continue;
                }
                const double t = static_cast<double>(m_strIndex - static_cast<int32>(index));
                auto drawPos = pos + glyph.getOffset();
                drawPos.y -= EaseIn(Easing::Quad, s3d::Saturate(1 - t / 4.0f)) * 20;

                auto alpha = static_cast<int32>(Saturate(t / 6.0) * 255.0);
                glyph.texture.draw(drawPos, color.setA(alpha));
                pos.x += glyph.xAdvance;
            }
        }
    }
}


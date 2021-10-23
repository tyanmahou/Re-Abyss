#include "TagStringView.hpp"
#include <Siv3D.hpp>

namespace abyss::Novel
{
    void TagStringView::Draw(
        const s3d::Font& font,
        const TagString& text,
        const s3d::Vec2& basePos,
        double time
    )
    {
        Vec2 pos = basePos;
        for (auto&& elm : text) {
            auto glyph = font.getGlyph(elm.ch);
            if (glyph.codePoint == U'\n') {
                pos.x = basePos.x;
                pos.y += font.height() + 4;
                continue;
            }
            auto drawPos = pos + glyph.getOffset();

            // さっと位置を動かす
            double t = (time - elm.time) / 60.0 * 1000.0;
            drawPos.y -= EaseIn(Easing::Quad, s3d::Saturate(1 - t / 4.0)) * 20;
            // アルファ調整
            auto alpha = Saturate(t / 6.0);

            glyph.texture.draw(drawPos, elm.color.setA(alpha));
            p.x += glyph.xAdvance;
        }
    }
}

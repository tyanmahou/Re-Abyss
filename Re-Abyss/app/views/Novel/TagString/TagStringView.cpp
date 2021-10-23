#include "TagStringView.hpp"
#include <Siv3D.hpp>

namespace
{
    Vec2 Shake(double t)
    {
        // オフセット計算
        auto periodTime = t * 11.4514 / 2.0;

        // ノイズ
        const double noise = s3d::Periodic::Sine0_1(1s, periodTime)
            + s3d::Periodic::Triangle0_1(s3d::Math::InvPi, t);

        // 左右に往復させるためのオフセット
        double offsetFactor = s3d::Periodic::Triangle0_1(1s, periodTime * 5.0);

        return Vec2::UnitX().rotated(noise * s3d::Math::TwoPi) * (2.0 * offsetFactor);
    }
}
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

            double t = time - elm.time;
            // さっと位置を動かす
            {
                constexpr double moveOffs = 20.0;
                constexpr double factor = 1.0 / 60.0 * 1000.0 / 4.0;
                drawPos.y -= EaseIn(Easing::Quad, s3d::Saturate(1 - t * factor)) * moveOffs;
            }
            // アルファ調整
            auto alpha = Saturate(t / 60.0 * 1000.0 / 6.0);

            // 揺らす
            if (elm.isShake) {
                drawPos += ::Shake(t);
            }

            glyph.texture.draw(drawPos, elm.color.setA(alpha));
            pos.x += glyph.xAdvance;
        }
    }
}

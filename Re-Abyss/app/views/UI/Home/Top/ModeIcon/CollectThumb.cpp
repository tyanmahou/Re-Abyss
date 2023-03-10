#include <abyss/views/UI/Home/Top/ModeIcon/CollectThumb.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/params/UI/Home/Top/ViewParam.hpp>

namespace abyss::UI::Home::Top
{
    CollectThumb::CollectThumb() :
        m_texture(Resource::Assets::Main()->load(U"UI/Home/ModeIcon.json"))
    {
    }
    void CollectThumb::drawUnselected(const s3d::Vec2& pos, [[maybe_unused]] double time, const s3d::ColorF(&colors)[2]) const
    {
        const auto& viewParam = ViewParam::CollectIcon();
        m_texture(U"collect_off_inv")
            .scaled(viewParam.iconScale)
            .drawAt(pos + viewParam.iconOffset, colors[0]);
        m_texture(U"collect_off")
            .scaled(viewParam.iconScale)
            .drawAt(pos + viewParam.iconOffset, colors[1]);
    }

    void CollectThumb::drawSelected(const s3d::Vec2& pos, double time, const s3d::ColorF(&colors)[2]) const
    {
        const auto& viewParam = ViewParam::CollectIcon();
        auto addScale = 1.0 + 0.1 * s3d::Saturate(time * 5);

        const Vec2 basePos = pos + viewParam.iconOffset + Vec2{-30, -10};
        const double baseScale = viewParam.iconScale * addScale;
        auto rotate = s3d::ToRadians(-20) * s3d::Saturate(time * 5)
            + s3d::ToRadians(5) * s3d::Periodic::Sine1_1(4s, time);

        m_texture(U"collect_on_inv")
            .scaled(baseScale)
            .rotatedAt(Vec2{120, 120} * baseScale + Vec2{ -30, -10 + 26 }, rotate)
            .drawAt(basePos, colors[0]);
        m_texture(U"collect_on")
            .scaled(baseScale)
            .rotatedAt(Vec2{ 120, 120} * baseScale + Vec2{ -30, -10 + 26 }, rotate)
            .drawAt(basePos, colors[1]);

        {
            auto alpha = s3d::Periodic::Square1_1(2s, time);
            m_texture(alpha > 0 ? U"collect_eft1" : U"collect_eft2")
                .scaled(baseScale)
                .rotatedAt(Vec2{ 120, 120 } *baseScale + Vec2{ -30, -10 + 26 }, s3d::ToRadians(-20))
                .drawAt(basePos, ColorF(colors[0], Abs(alpha)));
        }
    }
}

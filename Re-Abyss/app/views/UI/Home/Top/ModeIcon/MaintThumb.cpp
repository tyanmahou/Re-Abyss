#include <abyss/views/UI/Home/Top/ModeIcon/MaintThumb.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/params/UI/Home/Top/ViewParam.hpp>

namespace abyss::UI::Home::Top
{
    MaintThumb::MaintThumb() :
        m_texture(Resource::Assets::Main()->load(U"UI/Home/ModeIcon.json"))
    {
    }
    void MaintThumb::drawUnselected(const s3d::Vec2& pos, [[maybe_unused]] double time, const s3d::ColorF(&colors)[2]) const
    {
        const auto& viewParam = ViewParam::MaintIcon();
        m_texture(U"maint_off")
            .scaled(viewParam.iconScale)
            .drawAt(pos + viewParam.iconOffset, colors[1]);
    }
    void MaintThumb::drawSelected(const s3d::Vec2& pos, [[maybe_unused]] double time, const s3d::ColorF(&colors)[2]) const
    {
        const auto& viewParam = ViewParam::MaintIcon();
        auto addScale = 1.0 + 0.1 * s3d::Saturate(time * 5);

        const double baseScale = viewParam.iconScale * addScale;
        const Vec2 basePos = pos + viewParam.iconOffset + Vec2{ 0, 20 };

        double baseRate = s3d::Periodic::Sawtooth0_1(2.0, time);
        double rate = Min(baseRate, 0.9) / 0.9;
        rate = s3d::Pow(rate, s3d::Log(0.3) / s3d::Log(0.7));
        rate = s3d::Periodic::Triangle0_1(1.0s, rate);
        rate = 1 - (1 - rate) * (1 - rate) * (1 - rate);
        auto rotate = s3d::ToRadians(-60) * s3d::Saturate(time)
            + s3d::ToRadians(100) * rate;

        m_texture(U"maint_off")
            .scaled(viewParam.iconScale * addScale)
            .rotatedAt(Vec2{ 120 , 120} * baseScale + Vec2{ 0, 20 }, rotate)
            .drawAt(basePos, colors[1]);
    }
}

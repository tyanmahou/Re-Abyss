#include <abyss/views/UI/Home/Top/ModeIcon/GuildThumb.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/params/UI/Home/Top/ViewParam.hpp>
#include <abyss/views/util/Anim/AnimUtil.hpp>

namespace abyss::UI::Home::Top
{
    GuildThumb::GuildThumb() :
        m_texture(Resource::Assets::Main()->load(U"UI/Home/ModeIcon.json")),
        m_mask(Constants::AppResolution)
    {
    }
    void GuildThumb::drawUnselected(const s3d::Vec2& pos, [[maybe_unused]] double time, const s3d::ColorF(&colors)[2]) const
    {
        const auto& viewParam = ViewParam::GuildIcon();
        m_texture(U"guild_off_inv")
            .scaled(viewParam.iconScale)
            .drawAt(pos + viewParam.iconOffset, colors[0]);

        m_texture(U"guild_off")
            .scaled(viewParam.iconScale)
            .drawAt(pos + viewParam.iconOffset, colors[1]);
    }
    void GuildThumb::drawSelected(const s3d::Vec2& pos, double time, const s3d::ColorF(&colors)[2]) const
    {
        const auto& viewParam = ViewParam::GuildIcon();
        auto addScale = 1.0 + 0.1 * s3d::Saturate(time * 5);
        auto jump = s3d::Periodic::Jump0_1(1.0, s3d::Min(s3d::Periodic::Sawtooth0_1(4.0, time + 2.0), 0.05)* 20.0 ) * -5;
        const Vec2 basePos = pos + viewParam.iconOffset + Vec2{0, jump};
        auto t2d = Transformer2D(s3d::Mat3x2::Scale(addScale, basePos));

        size_t animeIndex = AnimUtil::FrameFromSaw(2.0, time, 4);
        constexpr double xOffsMap[4] = { 66.0, 60.0, 54.0, 0 };
        double xOffs = xOffsMap[animeIndex];

        m_texture(U"guild_off_inv")
            .scaled(viewParam.iconScale)
            .drawAt(basePos, colors[0]);
        {
            auto scopedMask = m_mask.equal([&] {
                RectF(basePos - Vec2{ 42, 120 }, 84, 240).draw();
            });
            double offs = s3d::Periodic::Sawtooth1_1(2s, time) * (42 + 10);
            LineString ls{
                basePos + Vec2 { offs - 100, 0 },
                basePos + Vec2 { offs - 10, 0},
                basePos + Vec2 { offs - 5, 20},
                basePos + Vec2 { offs + 5, -20},
                basePos + Vec2 { offs + 10, 0},
                basePos + Vec2 { offs + 100, 0},
            };
            ls.draw(ColorF(colors[1], 0.5));
        }
        m_texture(U"guild_on")(xOffs, 0, 240 - xOffs * 2, 240)
            .scaled(viewParam.iconScale)
            .drawAt(basePos, colors[1]);
        {
            auto alpha = 0.5 + 0.2 * s3d::Periodic::Triangle0_1(0.15, time);
            m_texture(U"guild_mark")
                .scaled(viewParam.iconScale)
                .drawAt(basePos, ColorF(colors[1], alpha));
        }
    }
}

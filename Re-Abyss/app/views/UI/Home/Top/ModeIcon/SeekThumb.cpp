#include <abyss/views/UI/Home/Top/ModeIcon/SeekThumb.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/params/UI/Home/Top/ViewParam.hpp>

namespace abyss::UI::Home::Top
{
    SeekThumb::SeekThumb():
        m_texture(Resource::Assets::Main()->load(U"UI/Home/ModeIcon.json")),
        m_mask(Constants::AppResolution)
    {
    }

    void SeekThumb::drawUnselected(const s3d::Vec2& pos, [[maybe_unused]] double time, const s3d::ColorF(&colors)[2]) const
    {
        const auto& viewParam = ViewParam::SeekIcon();
        m_texture(U"seek_off")
            .scaled(viewParam.iconScale)
            .drawAt(pos + viewParam.iconOffset, colors[1]);
    }
    void SeekThumb::drawSelected(const s3d::Vec2& pos, double time, const s3d::ColorF(&colors)[2]) const
    {
        const auto& viewParam = ViewParam::SeekIcon();
        auto addScale = 1.0
            + 0.05 * s3d::Saturate(time * 5)
            + 0.05 * s3d::Periodic::Sine0_1(5s, time);

        {
            auto scopedMask = m_mask.notEqual([&] {
                constexpr Vec2 baseSize{ 160, 160 };
                Vec2 size = baseSize * viewParam.scale;
                const RectF rect = RectF(pos - size / 2, size);
                const RectF scaled = rect.scaledAt(pos, 0.8);
                RectF(rect.x, scaled.y + scaled.h, Vec2{ 160 + 50, 50 })
                    .rotatedAt(pos, s3d::Math::QuarterPi)
                    .draw()
                    ;
                RectF(scaled.x + scaled.w, rect.y, Vec2{ 50, 160 + 50 })
                    .rotatedAt(pos, s3d::Math::QuarterPi)
                    .draw()
                    ;
            });
            m_texture(U"seek_off")
                .scaled(viewParam.iconScale * addScale)
                .drawAt(pos + viewParam.iconOffset, colors[1]);        }
    }
}

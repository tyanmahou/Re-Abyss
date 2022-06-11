#include <abyss/debugs/Log/LogViewer.hpp>
#include <Siv3D.hpp>

namespace abyss::Debug
{
    using namespace abyss::DebugLog;

    LogViewer::LogViewer() :
        m_font(16, Typeface::Regular),
        m_fontDetail(12, Typeface::Regular)
    {
        m_kindCustom[LogKind::Info] = KindCustom{
            .icon = Texture(Emoji(U"🗨️")),
            .color = ColorF(0, 0.2)
        };
        m_kindCustom[LogKind::Warn] = KindCustom{
            .icon = Texture(Emoji(U"⚠️")),
            .color = ColorF(1.0, 1.0, 0, 0.2)
        };
        m_kindCustom[LogKind::Error] = KindCustom{
            .icon = Texture(Emoji(U"❌")),
            .color = ColorF(1.0, 0, 0, 0.2)
        };
        m_kindCustom[LogKind::Load] = KindCustom{
            .icon = Texture(Emoji(U"❕")),
            .color = ColorF(1.0, 0.0, 1.0, 0.2)
        };
    }
    void LogViewer::draw(const s3d::Array<LogInfo>& logs) const
    {
        if (logs.isEmpty()) {
            return;
        }
        s3d::ScopedRenderStates2D sampler(s3d::SamplerState::ClampLinear);

        constexpr Vec2 iconSize{ 20,20 };
        constexpr double iconMargin = 5.0;
        // ウィンドウ幅
        double width = 0;
        for (const auto& log : logs) {
            width = s3d::Max(width, m_font(log.log()).region().w);
        }
        width += iconSize.x + iconMargin;
        width += 10;

        Vec2 pos{ 0, 0 };
        for (const auto& log : logs) {
            const auto& custom = m_kindCustom.at(log.kind());
            auto region = m_font(log.log()).region();
            region.w = width;
            region.h = s3d::Max(region.h, iconSize.y);

            auto area = RectF(pos, region.size);
            area.draw(custom.color);

            custom.icon.resized(iconSize).draw(pos);
            auto logPos = pos;
            logPos.x += iconSize.x + iconMargin;
            m_font(log.log()).draw(logPos);
            pos.y += region.h;

            if (area.mouseOver()) {
                auto detailRegion = m_fontDetail(log.location()).region(pos);
                detailRegion.draw(ColorF(0.2, 0.2));
                m_fontDetail(log.location()).draw(pos);
                pos = detailRegion.bl();
            }
        }
    }
}


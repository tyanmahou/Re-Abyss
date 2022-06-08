#include <abyss/utils/DebugLog/DebugLog.hpp>
#include <Siv3D.hpp>

namespace
{
    using namespace abyss;
    using namespace abyss::DebugLog;

    class LogInfo
    {
    public:
        LogInfo(
            LogKind kind,
            const s3d::String& log,
            const SourceLocation& location,
            s3d::int32 lifeTimeSec
        ) :
            m_kind(kind),
            m_log(log),
            m_location(location),
            m_lifeTimeMsec(lifeTimeSec)
        {}
        LogKind kind() const
        {
            return m_kind;
        }
        const s3d::String& log() const
        {
            return m_log;
        }
        s3d::String location() const
        {
            return U"{}({}:{}) {}"_fmt(
                s3d::FileSystem::RelativePath(m_location.fileName(), s3d::FileSystem::CurrentDirectory() + U"/../app"),
                m_location.line(),
                m_location.column(),
                m_location.functionName()
            );
        }

        bool isExpired() const
        {
            return m_sw.ms() >= m_lifeTimeMsec;
        }
    private:
        LogKind m_kind;
        s3d::String m_log;
        SourceLocation m_location;

        s3d::int32 m_lifeTimeMsec;
        s3d::Stopwatch m_sw{ StartImmediately::Yes };
    };

    class ISkin
    {
    public:
        virtual ~ISkin() = default;
        virtual void draw(const s3d::Array<LogInfo>& logs) const = 0;
    };
    class DefaultSkin : public ISkin
    {
        struct KindCustom
        {
            Texture icon;
            ColorF color;
        };
    public:
        DefaultSkin():
            m_font(16, Typeface::Regular),
            m_fontDetail(12, Typeface::Regular)
        {
            m_kindCustom[LogKind::Info] = KindCustom {
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
        void draw(const s3d::Array<LogInfo>& logs) const override
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

            Vec2 pos{0, 0};
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
    private:
        s3d::Font m_font;
        s3d::Font m_fontDetail;
        s3d::HashTable<LogKind, KindCustom> m_kindCustom;
    };
}
namespace abyss::DebugLog
{
    class DebugLog::Impl
    {
    public:
        Impl()
        {}
        void print(LogKind kind, const s3d::String& log, const SourceLocation& location)
        {
            m_buffer.emplace_back(kind, log, location, 10000);
        }
        void printUpdate(LogKind kind, const s3d::String& log, const SourceLocation& location)
        {
            m_buffer.emplace_back(kind, log, location, 0);
        }
        void update()
        {
            m_buffer.remove_if([](const LogInfo& log) {
                return log.isExpired();
            });
        }
        void clear()
        {
            m_buffer.clear();
        }
        void draw()
        {
            m_skin.draw(m_buffer);
        }
    private:
        s3d::Array<LogInfo> m_buffer;
        DefaultSkin m_skin;
    };

    DebugLog::DebugLog():
        m_pImpl(std::make_shared<Impl>())
    {
    }
    void DebugLog::print(LogKind kind, const s3d::String& log, const SourceLocation& location)
    {
        m_pImpl->print(kind, log, location);
    }
    void DebugLog::printUpdate(LogKind kind, const s3d::String& log, const SourceLocation& location)
    {
        m_pImpl->printUpdate(kind, log, location);
    }
    void DebugLog::clear()
    {
        m_pImpl->clear();
    }
    void DebugLog::update()
    {
        m_pImpl->update();
    }
    void DebugLog::draw() const
    {
        m_pImpl->draw();
    }
}

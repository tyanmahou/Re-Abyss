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
            const std::source_location& location,
            s3d::int32 lifeTimeSec
        ) :
            m_kind(kind),
            m_log(log),
            m_location(location),
            m_lifeTimeMsec(lifeTimeSec)
        {}

        const s3d::String& log() const
        {
            return m_log;
        }
        s3d::String fileName() const
        {
            return s3d::FileSystem::RelativePath(s3d::Unicode::Widen(m_location.file_name()));
        }
        s3d::uint32 line() const
        {
            return m_location.line();
        }

        bool isExpired() const
        {
            return m_sw.ms() >= m_lifeTimeMsec;
        }
    private:
        LogKind m_kind;
        s3d::String m_log;
        std::source_location m_location;

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
    public:
        DefaultSkin():
            m_font(16, Typeface::Regular)
        {}
        void draw(const s3d::Array<LogInfo>& logs) const override
        {
            if (logs.isEmpty()) {
                return;
            }
            // ウィンドウ幅
            double width = 0;
            for (const auto& log : logs) {
                width = s3d::Max(width, m_font(log.log()).region().w);
            }
            width += 10;

            Vec2 pos{0, 0};
            for (const auto& log : logs) {
                auto region = m_font(log.log()).region();
                region.w = width;
                RectF(pos, region.size).draw(ColorF(0, 0.2));
                m_font(log.log()).draw(pos);
                pos.y += region.h;
            }
        }
    private:
        s3d::Font m_font;
    };
}
namespace abyss::DebugLog
{
    class DebugLog::Impl
    {
    public:
        Impl()
        {}
        void print(LogKind kind, const s3d::String& log, const std::source_location& location)
        {
            m_buffer.emplace_back(kind, log, location, 10000);
        }
        void printUpdate(LogKind kind, const s3d::String& log, const std::source_location& location)
        {
            m_buffer.emplace_back(kind, log, location, 0);
        }
        void update()
        {
            m_buffer.remove_if([](const LogInfo& log) {
                return log.isExpired();
            });

            if (Key0.down()) {
                this->print(LogKind::Info, U"Test", std::source_location::current());
            }
            this->printUpdate(LogKind::Info, U"TestUpdate", std::source_location::current());
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
    void DebugLog::print(LogKind kind, const s3d::String& log, const std::source_location& location)
    {
        m_pImpl->print(kind, log, location);
    }
    void DebugLog::printUpdate(LogKind kind, const s3d::String& log, const std::source_location& location)
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

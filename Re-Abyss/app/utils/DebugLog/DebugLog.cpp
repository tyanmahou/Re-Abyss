#include <abyss/utils/DebugLog/DebugLog.hpp>
#include <Siv3D.hpp>

namespace
{
    using namespace abyss;
    using namespace abyss::DebugLog;

    struct LogInfo
    {
        LogKind kind;
        s3d::String log;
        std::source_location location;
    };

    struct LogModel : LogInfo
    {
        LogModel(const LogInfo& info, s3d::int32 lifeTimeSec):
            LogInfo(info),
            m_lifeTimeMsec(lifeTimeSec)
        {}

        bool isExpired() const
        {
            return m_sw.ms() >= m_lifeTimeMsec;
        }
    private:
        s3d::int32 m_lifeTimeMsec;
        s3d::Stopwatch m_sw{ StartImmediately::Yes };
    };
}
namespace abyss::DebugLog
{
    class DebugLog::Impl
    {
    public:
        Impl()
        {}
        void print(const LogInfo& log)
        {
            m_buffer.emplace_back(log, 10000);
        }
        void printUpdate(const LogInfo& log)
        {
            m_buffer.emplace_back(log, 0);
        }
        void update()
        {
            m_buffer.remove_if([](const LogModel& log) {
                return log.isExpired();
            });

            if (Key0.down()) {
                this->print({ LogKind::Info, U"Test", std::source_location::current() });
            }
            this->printUpdate({ LogKind::Info, U"TestUpdate", std::source_location::current() });
        }
        void clear()
        {
            m_buffer.clear();
        }
        void draw()
        {
            // TODO いい感じのViewerに変更
            s3d::ClearPrint();
            for (auto&& log : m_buffer) {
                const auto filePath = s3d::FileSystem::RelativePath(s3d::Unicode::Widen(log.location.file_name()));

                s3d::Print << log.log << filePath << log.location.line();
            }
        }
    private:
        s3d::Array<LogModel> m_buffer;
    };

    DebugLog::DebugLog():
        m_pImpl(std::make_shared<Impl>())
    {
    }
    void DebugLog::print(LogKind kind, const s3d::String& log, const std::source_location& location)
    {
        m_pImpl->print({
            .kind = kind,
            .log = log,
            .location = location
        });
    }
    void DebugLog::printUpdate(LogKind kind, const s3d::String& log, const std::source_location& location)
    {
        m_pImpl->printUpdate({
            .kind = kind,
            .log = log,
            .location = location
        });
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

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

    struct LogCache : LogInfo
    {
        size_t count;
        s3d::Stopwatch sw{ StartImmediately::Yes };
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

        }
        void printUpdate(const LogInfo& log)
        {
        }
        void update()
        {
        }
        void clear()
        {

        }
        void draw()
        {
        }
    private:
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

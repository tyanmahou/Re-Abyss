#include <abyss/utils/DebugLog/DebugLog.hpp>
#include <Siv3D.hpp>

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
            if (m_viewer) {
                m_viewer->draw(m_buffer);
            }
        }
        void setViewer(std::unique_ptr<IViewer>&& viewer)
        {
            m_viewer = std::move(viewer);
        }
    private:
        s3d::Array<LogInfo> m_buffer;
        std::unique_ptr<IViewer> m_viewer;
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
    void DebugLog::setViewer(std::unique_ptr<IViewer>&& viewer)
    {
        m_pImpl->setViewer(std::move(viewer));
    }
}

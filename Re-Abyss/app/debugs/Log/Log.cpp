#include <abyss/debugs/Log/Log.hpp>

#if ABYSS_DEBUG
#include <abyss/debugs/System/System.hpp>
#include <abyss/debugs/Log/LogViewer.hpp>

namespace abyss::Debug
{
    void Log::Info(const s3d::String& log, const SourceLocation& location)
    {
        System::GetLogViewer().printInfo(log, location);
    }
    void Log::InfoUpdate(const s3d::String& log, const SourceLocation& location)
    {
        System::GetLogViewer().printInfoUpdate(log, location);
    }
    void Log::Warn(const s3d::String& log, const SourceLocation& location)
    {
        System::GetLogViewer().printWarn(log, location);
    }
    void Log::WarnUpdate(const s3d::String& log, const SourceLocation& location)
    {
        System::GetLogViewer().printWarnUpdate(log, location);
    }
    void Log::Error(const s3d::String& log, const SourceLocation& location)
    {
        System::GetLogViewer().printError(log, location);
    }
    void Log::ErrorUpdate(const s3d::String& log, const SourceLocation& location)
    {
        System::GetLogViewer().printErrorUpdate(log, location);
    }
    void Log::Load(const s3d::String& log, const SourceLocation& location)
    {
        System::GetLogViewer().printLoad(log, location);
    }
    void Log::LoadUpdate(const s3d::String& log, const SourceLocation& location)
    {
        System::GetLogViewer().printLoadUpdate(log, location);
    }
    void Log::Clear()
    {
        System::GetLogViewer().clear();
    }
}
#endif

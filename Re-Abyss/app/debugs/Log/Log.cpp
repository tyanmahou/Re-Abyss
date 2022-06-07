#include <abyss/debugs/Log/Log.hpp>

#if ABYSS_DEBUG
#include <abyss/debugs/System/System.hpp>
#include <abyss/utils/DebugLog/DebugLog.hpp>

namespace abyss::Debug
{
    using DebugLog::LogKind;

    void Log::Info(const s3d::String& log, const SourceLocation& location)
    {
        System::GetLog().print(LogKind::Info, log, location);
    }
    void Log::InfoUpdate(const s3d::String& log, const SourceLocation& location)
    {
        System::GetLog().printUpdate(LogKind::Info, log, location);
    }
    void Log::Warn(const s3d::String& log, const SourceLocation& location)
    {
        System::GetLog().print(LogKind::Warn, log, location);
    }
    void Log::WarnUpdate(const s3d::String& log, const SourceLocation& location)
    {
        System::GetLog().printUpdate(LogKind::Warn, log, location);
    }
    void Log::Error(const s3d::String& log, const SourceLocation& location)
    {
        System::GetLog().print(LogKind::Error, log, location);
    }
    void Log::ErrorUpdate(const s3d::String& log, const SourceLocation& location)
    {
        System::GetLog().printUpdate(LogKind::Error, log, location);
    }
    void Log::Load(const s3d::String& log, const SourceLocation& location)
    {
        System::GetLog().print(LogKind::Load, log, location);
    }
    void Log::LoadUpdate(const s3d::String& log, const SourceLocation& location)
    {
        System::GetLog().printUpdate(LogKind::Load, log, location);
    }
    void Log::Clear()
    {
        System::GetLog().clear();
    }
}
#endif

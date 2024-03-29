#include <abyss/utils/DebugLog/LogInfo.hpp>

namespace abyss::DebugLog
{
    LogInfo::LogInfo(
        LogKind kind,
        const s3d::String& log,
        const SourceLocation& location
    ) :
        m_kind(kind),
        m_log(log),
        m_location(location)
    {}

    s3d::String LogInfo::location() const
    {
        return U"{}({}:{}) {}"_fmt(
            s3d::FileSystem::RelativePath(m_location.fileName(), s3d::FileSystem::CurrentDirectory() + U"/../app"),
            m_location.line(),
            m_location.column(),
            m_location.functionName()
        );
    }
}


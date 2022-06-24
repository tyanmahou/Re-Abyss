#pragma once
#include <abyss/utils/DebugLog/LogKind.hpp>
#include <abyss/utils/SourceLocation/SourceLocation.hpp>
#include <Siv3D/Stopwatch.hpp>

namespace abyss::DebugLog
{
    class LogInfo
    {
    public:
        LogInfo(
            LogKind kind,
            const s3d::String& log,
            const SourceLocation& location
        );

        LogKind kind() const
        {
            return m_kind;
        }
        const s3d::String& log() const
        {
            return m_log;
        }
        s3d::String location() const;
    private:
        LogKind m_kind;
        s3d::String m_log;
        SourceLocation m_location;
    };

}

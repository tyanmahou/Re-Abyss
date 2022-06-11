#pragma once
#include <abyss/utils/DebugLog/LogInfo.hpp>
#include <Siv3D/Array.hpp>

namespace abyss::DebugLog
{
    class IViewer
    {
    public:
        virtual ~IViewer() = default;
        virtual void draw(const s3d::Array<LogInfo>& logs) const = 0;
    };
}

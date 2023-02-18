#pragma once
#if ABYSS_DEBUG
#include <concepts>
#include <abyss/utils/SourceLocation/SourceLocation.hpp>

namespace abyss::Debug
{
    /// <summary>
    /// デバッグログ
    /// </summary>
    class Log
    {
    public:
#define ABYSS_DEBUG_LOG(kind) \
        template<class T> requires !std::constructible_from<s3d::String, T>\
        static void kind(T&& log, const SourceLocation& location = {})\
        {\
            kind(s3d::String(U"{}"_fmt(std::forward<T>(log))), location);\
        }\
        static void kind(const s3d::String& log, const SourceLocation& location = {})

        ABYSS_DEBUG_LOG(Info);

        ABYSS_DEBUG_LOG(Alert);

        ABYSS_DEBUG_LOG(Warn);

        ABYSS_DEBUG_LOG(Error);

        ABYSS_DEBUG_LOG(Load);

#undef ABYSS_DEBUG_LOG

        static void Clear();
    };
}
#endif

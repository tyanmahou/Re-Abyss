#pragma once
#if ABYSS_DEBUG
#include <concepts>

namespace abyss::Debug
{
    /// <summary>
    /// ウォッチャー
    /// </summary>
    class Watcher
    {
    public:
        static void Print(const s3d::String& log);
    };
}
#endif

#pragma once
#if ABYSS_DEBUG
#include <abyss/debugs/HotReload/FileChanges.hpp>

namespace abyss::Debug
{
    class HotReloadUtil
    {
    public:
        static void ReloadAssetCommon(const FileChanges& changes = {});
    };
}
#endif

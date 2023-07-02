#pragma once
#if ABYSS_DEBUG
#include <Siv3D/DirectoryWatcher.hpp>
#include <Siv3D/Array.hpp>
#include <Siv3D/Optional.hpp>

namespace abyss::Debug
{
    class HotReloadUtil
    {
    public:
        static void ReloadAssetCommon(const s3d::Optional<s3d::Array<s3d::FileChange>>& changes = s3d::none);
    };
}
#endif

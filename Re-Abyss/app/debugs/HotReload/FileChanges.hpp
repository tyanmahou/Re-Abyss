#pragma once
#if ABYSS_DEBUG
#include <Siv3D/DirectoryWatcher.hpp>
#include <Siv3D/Array.hpp>
#include <Siv3D/Optional.hpp>

namespace abyss::Debug
{
    using FileChanges = s3d::Array<s3d::FileChange>;
}
#endif

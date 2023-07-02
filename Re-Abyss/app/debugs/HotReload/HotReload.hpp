#pragma once
#if ABYSS_DEBUG
#include <functional>
#include <Siv3D/DirectoryWatcher.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/debugs/HotReload/HotReloadUtil.hpp>

namespace abyss::Debug
{
    using FileChanges = s3d::Optional<s3d::Array<s3d::FileChange>>;

    class HotReload
    {
    public:
#if ABYSS_NO_BUILD_RESOURCE
        HotReload(const s3d::FilePath& path = Path::ResourcePath);
#else
        HotReload();
#endif
        HotReload& setMessage(const s3d::String& message);
        HotReload& setCallback(const std::function<void(FileChanges)>& callback);
        HotReload& setSuperCallback(const std::function<void()>& callback);

        [[nodiscard]] bool onModify() const;

        bool detection() const;
    private:
#if ABYSS_NO_BUILD_RESOURCE
        s3d::DirectoryWatcher m_watcher;
#endif
        s3d::String m_message;
        std::function<void(FileChanges)> m_callback;
        std::function<void()> m_superCallback;
    };
}

#endif

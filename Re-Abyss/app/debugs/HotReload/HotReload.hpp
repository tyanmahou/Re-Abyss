#pragma once
#if ABYSS_DEBUG
#include <functional>
#include <Siv3D/DirectoryWatcher.hpp>
#include <abyss/commons/ResourceManager/ResourceManager.hpp>

namespace abyss::Debug
{
    class HotReload
    {
    private:
        s3d::DirectoryWatcher m_watcher;
        s3d::String m_message;
        std::function<void()> m_callback;
    public:
        HotReload(const s3d::FilePath& path = Path::ResourcePath);

        HotReload& setMessage(const s3d::String& message);
        HotReload& setCallback(const std::function<void()>& callback);

        [[nodiscard]] bool onModify() const;

        bool detection() const;
    };
}

#endif
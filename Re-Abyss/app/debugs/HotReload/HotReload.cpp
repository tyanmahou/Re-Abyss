#if ABYSS_DEBUG
#include <abyss/debugs/HotReload/HotReload.hpp>

#include <Siv3D/FileSystem.hpp>
#include <Siv3D/Keyboard.hpp>
#include <Siv3D/Input.hpp>
#include <abyss/debugs/Log/Log.hpp>

namespace abyss::Debug
{
#if ABYSS_NO_BUILD_RESOURCE
    HotReload::HotReload(const s3d::FilePath& path):
        m_watcher(s3d::FileSystem::FullPath(path))
    {}
#else
    HotReload::HotReload()
    {}
#endif

    HotReload& HotReload::setMessage(const s3d::String & message)
    {
        m_message = message;
        return *this;
    }

    HotReload& HotReload::setCallback(const std::function<void(FileChanges)>& callback)
    {
        m_callback = callback;
        return *this;
    }

    HotReload& HotReload::setSuperCallback(const std::function<void()>& callback)
    {
        m_superCallback = callback;
        return *this;
    }

    bool HotReload::onModify(FileChanges& out) const
    {
#if ABYSS_NO_BUILD_RESOURCE
        return m_watcher.retrieveChanges(out);
#else
        return false;
#endif
    }

    bool HotReload::detection() const
    {
        if ((s3d::KeyControl + s3d::KeyF5).down()) {
            Debug::Log::Info(U"Super Reload: {}"_fmt(m_message));

            if (m_superCallback) {
                m_superCallback();
            } else if (m_callback) {
                m_callback({});
            }
            return true;
        }

        FileChanges changes{};
        if (s3d::KeyF5.down() || this->onModify(changes)) {
            Debug::Log::Info(U"Reload: {}"_fmt(m_message));

            if (m_callback) {
                m_callback(changes);
            }
            return true;
        }

        return false;
    }

}
#endif

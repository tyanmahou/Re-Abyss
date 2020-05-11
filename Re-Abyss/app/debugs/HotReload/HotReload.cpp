#if ABYSS_DEBUG
#include "HotReload.hpp"

#include <Siv3D/FileSystem.hpp>
#include <Siv3D/Keyboard.hpp>
#include <abyss/debugs/DebugLog/DebugLog.hpp>

namespace abyss::Debug
{
    HotReload::HotReload(const s3d::FilePath& path):
        m_watcher(s3d::FileSystem::FullPath(path))
    {}

    HotReload& HotReload::setMessage(const s3d::String & message)
    {
        m_message = message;
        return *this;
    }

    HotReload& HotReload::setCallback(const std::function<void()>& callback)
    {
        m_callback = callback;
        return *this;
    }

    bool HotReload::onModify() const
    {
        return s3d::KeyF5.down() || m_watcher.retrieveChanges().size() > 0;
    }

    bool HotReload::detection() const
    {
        if (!this->onModify()) {
            return false;
        }
        DebugLog::PrintCache << U"Reload: " << m_message;

        if (m_callback) {
            m_callback();
        }

        return true;
    }

}
#endif
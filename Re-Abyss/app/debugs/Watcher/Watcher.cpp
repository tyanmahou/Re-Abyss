#include <abyss/debugs/Watcher/Watcher.hpp>

#if ABYSS_DEBUG
#include <abyss/debugs/System/System.hpp>
#include <abyss/debugs/Watcher/WatchViewer.hpp>

namespace abyss::Debug
{
    void Watcher::Print(const s3d::String& log)
    {
        System::GetWatchViewer().print(log);
    }
}
#endif

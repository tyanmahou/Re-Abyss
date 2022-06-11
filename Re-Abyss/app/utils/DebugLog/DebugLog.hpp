#pragma once
#include <memory>
#include <abyss/utils/DebugLog/LogInfo.hpp>
#include <abyss/utils/DebugLog/IViewer.hpp>

namespace abyss::DebugLog
{
    /// <summary>
    /// デバッグログ
    /// </summary>
    class DebugLog
    {
        class Impl;
    public:
        DebugLog();

        void print(LogKind kind, const s3d::String& log, const SourceLocation& location = {});
        void printUpdate(LogKind kind, const s3d::String& log, const SourceLocation& location = {});
        void clear();

        void update();
        void draw() const;

        template<class Viewer, class... Args>
        void setViewer(Args&&... args)
        {
            this->setViewer(std::make_unique<Viewer>(std::forward<Args>(args)...));
        }
        void setViewer(std::unique_ptr<IViewer>&& viewer);
    private:
        std::shared_ptr<Impl> m_pImpl;
    };
}

#pragma once
#if ABYSS_DEBUG
#include <memory>
#include <abyss/utils/SourceLocation/SourceLocation.hpp>

namespace abyss::Debug
{
    class LogViewer
    {
        class Impl;
    public:
        LogViewer();

        void update();
        void draw() const;

        void printInfo(const s3d::String& log, const SourceLocation& location);

        void printAlert(const s3d::String& log, const SourceLocation& location);

        void printWarn(const s3d::String& log, const SourceLocation& location);

        void printError(const s3d::String& log, const SourceLocation& location);

        void printLoad(const s3d::String& log, const SourceLocation& location);

        void clear();
    private:
        std::shared_ptr<Impl> m_pImpl;
    };
}
#endif

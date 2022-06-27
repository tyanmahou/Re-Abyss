#pragma once
#if ABYSS_DEBUG
#include <concepts>

namespace abyss::Debug
{
    class WatchViewer
    {
        class Impl;
    public:
        WatchViewer();

        void update();
        void draw() const;

        void print(const s3d::String& log);
    private:
        std::shared_ptr<Impl> m_pImpl;
    };
}
#endif

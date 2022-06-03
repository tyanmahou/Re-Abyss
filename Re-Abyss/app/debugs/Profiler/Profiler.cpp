#if ABYSS_DEBUG
#include <abyss/debugs/Profiler/Profiler.hpp>
#include <abyss/debugs/Menu/Menu.hpp>
#include <Siv3D.hpp>

namespace abyss::Debug
{
    class Profiler::Impl
    {
    public:
        void begin(const s3d::StringView name)
        {
            m_profiler.begin(name);
        }
        void end(const s3d::StringView name)
        {
            m_profiler.end(name);
        }
        void print()
        {
            m_profiler.print();
        }
    private:
        TimeProfiler m_profiler{U"Profiler"};
    };
    Profiler::Profiler():
        m_pImpl(std::make_unique<Impl>())
    {}
    void Profiler::begin(const s3d::StringView name)
    {
        m_pImpl->begin(name);
    }
    void Profiler::end(const s3d::StringView name)
    {
        m_pImpl->end(name);
    }
    void Profiler::print()
    {
        if (Menu::IsDebug(DebugFlag::AlertProfiler)) {
            m_pImpl->print();
        }
    }
}

#endif

#if ABYSS_DEBUG
#include "Profiler.hpp"
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
    void Profiler::Begin(const s3d::StringView name)
    {
        Instance()->m_pImpl->begin(name);
    }
    void Profiler::End(const s3d::StringView name)
    {
        Instance()->m_pImpl->end(name);
    }
    void Profiler::Print()
    {
        if (Menu::IsDebug(DebugFlag::AlertProfiler)) {
            Instance()->m_pImpl->print();
        }
    }
}

#endif
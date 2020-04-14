#include "DebugLog.hpp"
#if ABYSS_DEBUG
namespace abyss
{
    class DebugLog::Impl
    {
        std::size_t m_maxCacheSize = 3;
        std::list<s3d::String> m_printCache;
    public:
        void printCache(const s3d::String& log)
        {
            m_printCache.push_back(log);
            if (m_printCache.size() > m_maxCacheSize) {
                m_printCache.pop_front();
            }
        }
        void print(const s3d::String& log)const
        {
            s3d::Print << log;
        }
        void clearAndPrintCached()const
        {
            s3d::ClearPrint();
            for (const auto& log : m_printCache) {
                s3d::Print << log;
            }
        }
        void clear()
        {
            s3d::ClearPrint();
            m_printCache.clear();
        }
        void setMaxCacheSize(std::size_t size)
        {
            m_maxCacheSize = size;
        }
    };

    DebugLog::DebugLog():
        m_pImpl(std::make_unique<Impl>())
    {}

    void DebugLog::SetMaxCacheSize(std::size_t size)
    {
        Instance()->m_pImpl->setMaxCacheSize(size);
    }

    void DebugLog::Clear()
    {
        Instance()->m_pImpl->clear();
    }

    void DebugLog::ClearAndPrintCached()
    {
        Instance()->m_pImpl->clearAndPrintCached();
    }

    void DebugLog::PrintCacheImpl::writeln(const s3d::String& log) const
    {
        DebugLog::Instance()->m_pImpl->printCache(log);
    }

}
#endif
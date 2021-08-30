#include "Log.hpp"

#if ABYSS_DEBUG
#include <Siv3D.hpp>

namespace abyss::Debug
{
    // -------------------------------------------------
    class LogUpdater::Impl
    {
        struct Cache
        {
            s3d::Stopwatch sw;
            s3d::String log;

            Cache() = default;
            Cache(const s3d::String& _log):
                sw(true),
                log(_log)
            {}
        };
        s3d::Array<Cache> m_printCache;
    public:
        void print(const s3d::String& log)
        {
            m_printCache.emplace_back(log);
        }
        void printUpdate(const s3d::String& log)const
        {
            s3d::Print << log;
        }
        void update()
        {
            s3d::ClearPrint();
            for (const auto& cache : m_printCache.remove_if([](const Cache& cache) {
                return cache.sw.ms() >= 10000.0;
            })) {
                s3d::Print << cache.log;
            }
        }
        void clear()
        {
            s3d::ClearPrint();
            m_printCache.clear();
        }
    };

    LogUpdater::LogUpdater():
        m_pImpl(std::make_unique<Impl>())
    {}

    void LogUpdater::Update()
    {
        Instance()->m_pImpl->update();
    }
    void LogUpdater::Clear()
    {
        Instance()->m_pImpl->clear();
    }

    void LogUpdater::Print(const s3d::String& log)
    {
        Instance()->m_pImpl->print(log);
    }

    void LogUpdater::PrintUpdate(const s3d::String & log)
    {
        Instance()->m_pImpl->printUpdate(log);
    }

    namespace detail
    {
        // -------------------------------------------------
        template<class Tag, LogMethod Method>
        LogBuffer<Tag, Method>::LogBuffer() :
            formatData(std::make_unique<s3d::FormatData>())
        {}

        template<class Tag, LogMethod Method>
        LogBuffer<Tag, Method>::LogBuffer(LogBuffer&& other) noexcept :
            formatData(std::move(other.formatData))
        {}

        template<class Tag, LogMethod Method>
        LogBuffer<Tag, Method>::~LogBuffer()
        {
            if (formatData) {
                if constexpr (Method == LogMethod::Update) {
                    LogWriter<Tag>{}.writeUpdate(formatData->string);
                } else {
                    LogWriter<Tag>{}.write(formatData->string);
                }
            }
        }

        // -------------------------------------------------

        template<class Tag>
        void LogWriter<Tag>::write(const s3d::String& log) const
        {
            LogUpdater::Print(log);
        }
        template<class Tag>
        void LogWriter<Tag>::writeUpdate(const s3d::String& log) const
        {
            LogUpdater::PrintUpdate(log);
        }

        template struct LogWriter<Tag::Normal>;
        template struct LogBuffer<Tag::Normal, LogMethod::Normal>;
        template struct LogBuffer<Tag::Normal, LogMethod::Update>;

        template struct LogWriter<Tag::Warn>;
        template struct LogBuffer<Tag::Warn, LogMethod::Normal>;
        template struct LogBuffer<Tag::Warn, LogMethod::Update>;

        template struct LogWriter<Tag::Error>;
        template struct LogBuffer<Tag::Error, LogMethod::Normal>;
        template struct LogBuffer<Tag::Error, LogMethod::Update>;

        template struct LogWriter<Tag::Load>;
        template struct LogBuffer<Tag::Load, LogMethod::Normal>;
        template struct LogBuffer<Tag::Load, LogMethod::Update>;

    }
}
#endif
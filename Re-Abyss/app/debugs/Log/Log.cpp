#include "Log.hpp"

#if ABYSS_DEBUG
#include <Siv3D.hpp>
#include <abyss/debugs/Menu/Menu.hpp>

namespace abyss::Debug
{
    // -------------------------------------------------
    class LogUpdater::Impl
    {
        struct LogInfo
        {
            LogKind kind;
            s3d::String log;

            bool isVisble() const
            {
                if (!Menu::IsDebug(DebugFlag::LogIsVisible)) {
                    return false;
                }
                switch (kind) {
                case LogKind::Normal:
                    return Menu::IsDebug(DebugFlag::LogNormal);
                case LogKind::Warn:
                    return Menu::IsDebug(DebugFlag::LogWarn);
                case LogKind::Error:
                    return Menu::IsDebug(DebugFlag::LogError);
                case LogKind::Load:
                    return Menu::IsDebug(DebugFlag::LogLoad);
                default:
                    break;
                }
                return true;
            }
            void print() const
            {
                if (!isVisble()) {
                    return;
                }
                s3d::Print << log;
            }
        };
        struct Cache : LogInfo
        {
            s3d::Stopwatch sw{true};
        };
        s3d::Array<Cache> m_printCache;
    public:
        void print(LogKind kind, const s3d::String& log)
        {
            m_printCache.push_back(Cache{ kind, log });
        }
        void printUpdate(LogKind kind, const s3d::String& log)const
        {
            LogInfo{ kind, log }.print();
        }
        void update()
        {
            s3d::ClearPrint();
            for (const auto& cache : m_printCache.remove_if([](const Cache& cache) {
                return cache.sw.ms() >= 10000.0;
            })) {
                cache.print();
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

    void LogUpdater::Print(LogKind kind, const s3d::String& log)
    {
        Instance()->m_pImpl->print(kind, log);
    }

    void LogUpdater::PrintUpdate(LogKind kind, const s3d::String & log)
    {
        Instance()->m_pImpl->printUpdate(kind, log);
    }

    namespace detail
    {
        // -------------------------------------------------
        template<LogKind Kind, LogMethod Method>
        LogBuffer<Kind, Method>::LogBuffer() :
            formatData(std::make_unique<s3d::FormatData>())
        {}

        template<LogKind Kind, LogMethod Method>
        LogBuffer<Kind, Method>::LogBuffer(LogBuffer&& other) noexcept :
            formatData(std::move(other.formatData))
        {}

        template<LogKind Kind, LogMethod Method>
        LogBuffer<Kind, Method>::~LogBuffer()
        {
            if (formatData) {
                if constexpr (Method == LogMethod::Update) {
                    LogWriter<Kind>{}.writeUpdate(formatData->string);
                } else {
                    LogWriter<Kind>{}.write(formatData->string);
                }
            }
        }

        // -------------------------------------------------

        template<LogKind Kind>
        void LogWriter<Kind>::write(const s3d::String& log) const
        {
            LogUpdater::Print(Kind, log);
        }
        template<LogKind Kind>
        void LogWriter<Kind>::writeUpdate(const s3d::String& log) const
        {
            LogUpdater::PrintUpdate(Kind, log);
        }

        template struct LogWriter<LogKind::Normal>;
        template struct LogBuffer<LogKind::Normal, LogMethod::Normal>;
        template struct LogBuffer<LogKind::Normal, LogMethod::Update>;

        template struct LogWriter<LogKind::Warn>;
        template struct LogBuffer<LogKind::Warn, LogMethod::Normal>;
        template struct LogBuffer<LogKind::Warn, LogMethod::Update>;

        template struct LogWriter<LogKind::Error>;
        template struct LogBuffer<LogKind::Error, LogMethod::Normal>;
        template struct LogBuffer<LogKind::Error, LogMethod::Update>;

        template struct LogWriter<LogKind::Load>;
        template struct LogBuffer<LogKind::Load, LogMethod::Normal>;
        template struct LogBuffer<LogKind::Load, LogMethod::Update>;

    }
}
#endif
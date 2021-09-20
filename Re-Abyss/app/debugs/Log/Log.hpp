#pragma once
#if ABYSS_DEBUG
#include <Siv3D/Print.hpp>
#include <abyss/utils/Singleton/DynamicSingleton.hpp>

namespace abyss::Debug
{
    enum class LogKind
    {
        Normal,
        Warn,
        Error,
        Load,
    };
    namespace detail
    {
        enum class LogMethod
        {
            Normal,
            Update,
        };
        template<LogKind Kind, LogMethod Method = LogMethod::Normal>
        struct LogBuffer
        {
            std::unique_ptr<s3d::FormatData> formatData;

            LogBuffer();
            LogBuffer(LogBuffer&& other) noexcept;
            ~LogBuffer();

            template<s3d::Concept::Formattable Type>
            LogBuffer& operator << (const Type& value)
            {
                Formatter(*formatData, value);
                return *this;
            }
        };

        template<LogKind Kind>
        struct LogWriter
        {
            template<LogMethod Method>
            struct Helper
            {
                template<s3d::Concept::Formattable Type>
                LogBuffer<Kind, Method> operator << (const Type& value)const
                {
                    LogBuffer<Kind, Method> buf;
                    Formatter(*buf.formatData, value);
                    return buf;
                }
            };
        public:
            static constexpr Helper<LogMethod::Update> Update{};
        public:
            void write(const s3d::String& log) const;
            void writeUpdate(const s3d::String& log) const;

            template<s3d::Concept::Formattable Type>
            LogBuffer<Kind> operator << (const Type& value)const
            {
                LogBuffer<Kind> buf;
                Formatter(*buf.formatData, value);
                return buf;
            }
        };
    }

    class LogUpdater final : private DynamicSingleton<LogUpdater>
    {
        friend DynamicSingleton<LogUpdater>;
    public:
        static void Update();
        static void Clear();

        static void Print(LogKind kind, const s3d::String& log);
        static void PrintUpdate(LogKind kind, const s3d::String& log);

    private:
        class Impl;
        LogUpdater();
        std::unique_ptr<Impl> m_pImpl;
    };

    inline constexpr auto Log = detail::LogWriter<LogKind::Normal>{};
    inline constexpr auto LogWarn = detail::LogWriter<LogKind::Warn>{};
    inline constexpr auto LogError = detail::LogWriter<LogKind::Error>{};
    inline constexpr auto LogLoad = detail::LogWriter<LogKind::Load>{};
}
#endif
#pragma once
#if ABYSS_DEBUG
#include <Siv3D/Format.hpp>
#include <abyss/utils/Singleton/DynamicSingleton.hpp>

namespace abyss::Debug
{
    namespace detail
    {
        namespace Tag
        {
            struct Normal;
            struct Warn;
            struct Error;
            struct Load;
        }
        enum class LogMethod
        {
            Normal,
            Update,
        };
        template<class Tag, LogMethod Method = LogMethod::Normal>
        struct LogBuffer
        {
            std::unique_ptr<s3d::FormatData> formatData;

            LogBuffer();
            LogBuffer(LogBuffer&& other) noexcept;
            ~LogBuffer();

            template<class Type>
            LogBuffer& operator << (const Type& value)
            {
                s3d::Formatter(*formatData, value);
                return *this;
            }
        };

        template<class Tag>
        struct LogWriter
        {
            template<LogMethod Method>
            struct Helper
            {
                template<class Type>
                LogBuffer<Tag, Method> operator << (const Type& value)const
                {
                    LogBuffer<Tag, Method> buf;
                    s3d::Formatter(*buf.formatData, value);
                    return buf;
                }
            };
        public:
            static constexpr Helper<LogMethod::Update> Update{};
        public:
            void write(const s3d::String& log) const;
            void writeUpdate(const s3d::String& log) const;

            template<class Type>
            LogBuffer<Tag> operator << (const Type& value)const
            {
                LogBuffer<Tag> buf;
                s3d::Formatter(*buf.formatData, value);
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

        static void Print(const s3d::String& log);
        static void PrintUpdate(const s3d::String& log);

    private:
        class Impl;
        LogUpdater();
        std::unique_ptr<Impl> m_pImpl;
    };

    inline constexpr auto Log = detail::LogWriter<detail::Tag::Normal>{};
    inline constexpr auto LogWarn = detail::LogWriter<detail::Tag::Warn>{};
    inline constexpr auto LogError = detail::LogWriter<detail::Tag::Error>{};
    inline constexpr auto LogLoad = detail::LogWriter<detail::Tag::Load>{};
}
#endif
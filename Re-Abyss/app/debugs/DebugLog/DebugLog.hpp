#pragma once
#if ABYSS_DEBUG
#include <Siv3D/Print.hpp>
#include <abyss/utils/Singleton.hpp>
namespace abyss
{
    class DebugLog final : private Singleton<DebugLog>
    {
        friend Singleton<DebugLog>;
    public:
        struct PrintCacheBuffer
        {
            std::unique_ptr<s3d::FormatData> m_formatData;
            PrintCacheBuffer():
                m_formatData(std::make_unique<s3d::FormatData>())
            {}
            PrintCacheBuffer(PrintCacheBuffer&& other) noexcept :
                m_formatData(std::move(other.m_formatData))
            {}
            ~PrintCacheBuffer()
            {
                PrintCacheImpl{}.writeln(m_formatData->string);
            }

            template<class Type>
            PrintCacheBuffer& operator << (const Type& value)
            {
                s3d::Formatter(*m_formatData, value);
                return *this;
            }
        };

        struct PrintCacheImpl
        {
        public:
            void writeln(const s3d::String& log) const;

            template<class Type>
            PrintCacheBuffer operator << (const Type& value)const
            {
                PrintCacheBuffer buf;
                s3d::Formatter(*buf.m_formatData, value);
                return buf;
            }
        };
    private:
        class Impl;
        std::unique_ptr<Impl> m_pImpl;
        DebugLog();
    public:
        static void SetMaxCacheSize(std::size_t size);
        static void Clear();
        static void ClearAndPrintCached();

        inline static constexpr s3d::detail::Print_impl Print{};
        inline static constexpr PrintCacheImpl PrintCache{};
    };
}
#endif
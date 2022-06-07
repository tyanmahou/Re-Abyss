#pragma once
#include <source_location>
#include <Siv3D/String.hpp>
#include <Siv3D/Types.hpp>

namespace abyss
{
    struct SourceLocation
    {
        static consteval SourceLocation Current(const SourceLocation& result = {}) {
            return result;
        }

        constexpr SourceLocation(
            const uint_least32_t line = __builtin_LINE(),
            const uint_least32_t column = __builtin_COLUMN(),
            const char* const file = __builtin_FILE(),
            const char* const function = __builtin_FUNCTION()
        ) noexcept :
            m_line(line),
            m_column(column),
            m_file(file),
            m_function(function)
        {}

        constexpr explicit SourceLocation(const std::source_location& other) noexcept :
            SourceLocation(other.line(), other.column(), other.file_name(), other.function_name())
        {}

        [[nodiscard]] constexpr s3d::uint32 line() const noexcept
        {
            return m_line;
        }

        [[nodiscard]] constexpr s3d::uint32 column() const noexcept
        {
            return m_column;
        }

        [[nodiscard]] s3d::String fileName() const
        {
            return s3d::Unicode::Widen(m_file);
        }

        [[nodiscard]] s3d::String functionName() const
        {
            return s3d::Unicode::Widen(m_function);
        }
    private:
        s3d::uint32 m_line{};
        s3d::uint32 m_column{};
        const char* m_file = "";
        const char* m_function = "";
    };
}

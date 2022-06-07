#pragma once
#include <source_location>
#include <Siv3D/String.hpp>
#include <Siv3D/Types.hpp>

namespace abyss
{
    struct SourceLocation
    {
        static consteval SourceLocation Current()
        {
            return {};
        }

        constexpr SourceLocation(const std::source_location& location = std::source_location::current()) noexcept :
            m_location(location)
        {}

        [[nodiscard]] constexpr s3d::uint32 line() const noexcept
        {
            return static_cast<s3d::uint32>(m_location.line());
        }

        [[nodiscard]] constexpr s3d::uint32 column() const noexcept
        {
            return static_cast<s3d::uint32>(m_location.column());
        }

        [[nodiscard]] s3d::String fileName() const
        {
            return s3d::Unicode::Widen(m_location.file_name());
        }

        [[nodiscard]] s3d::String functionName() const
        {
            return s3d::Unicode::Widen(m_location.function_name());
        }
    private:
        std::source_location m_location;
    };
}

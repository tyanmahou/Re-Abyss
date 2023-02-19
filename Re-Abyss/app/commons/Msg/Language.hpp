#pragma once
#include <Siv3D/String.hpp>

namespace abyss::Msg
{
    class Language
    {
    public:
        [[nodiscard]] static constexpr Language Ja()
        {
            return Language(U"ja");
        }
    public:
        [[nodiscard]] constexpr s3d::StringView toStrView() const
        {
            return m_language;
        }
    private:
        constexpr Language(s3d::StringView language):
            m_language(language)
        {}
    public:
        s3d::StringView m_language;
    };
}

#pragma once
#include <Siv3D/String.hpp>

namespace abyss::Msg
{
    class Language
    {
    public:
        [[nodiscard]] static Language Ja();
    public:
        const s3d::String& toStr() const
        {
            return m_language;
        }
    private:
        Language(const s3d::String& language);
    public:
        s3d::String m_language;
    };
}

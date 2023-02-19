#include <abyss/commons/Msg/Language.hpp>

namespace abyss::Msg
{
    Language Language::Ja()
    {
        return Language(U"ja");
    }

    Language::Language(const s3d::String& language):
        m_language(language)
    {
    }
}

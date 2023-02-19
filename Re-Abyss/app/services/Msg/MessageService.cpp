#include <abyss/services/Msg/MessageService.hpp>

namespace abyss::Resource::Msg
{
    MessageService::MessageService(const Language& lang) :
        m_lang(lang)
    {
    }
    s3d::Array<std::pair<s3d::String, s3d::String>> MessageService::getMessages(s3d::StringView category) const
    {
        return m_dataStore->select(category, m_lang);
    }
}


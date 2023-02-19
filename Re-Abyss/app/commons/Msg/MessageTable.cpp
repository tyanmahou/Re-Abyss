#include <abyss/commons/Msg/MessageTable.hpp>

namespace abyss::Msg
{
    void MessageTable::add(const Label& label, s3d::String message)
    {
        add(label.category, label.key, std::move(message));
    }
    void MessageTable::add(s3d::StringView category, s3d::StringView key, s3d::String message)
    {
        m_table[category][key] = std::move(message);
    }
    const s3d::String& MessageTable::get(const Label& label)
    {
        // NOTE: Stringのアロケーションなしでいけてる？
        return m_table[label.category][label.key];
    }
}

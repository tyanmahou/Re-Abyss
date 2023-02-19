#include <abyss/commons/Msg/MessageTable.hpp>

namespace abyss::Msg
{
    void MessageTable::add(const Label& label, s3d::String message)
    {
        add(label.category, label.key, std::move(message));
    }
    void MessageTable::add(const s3d::String& category, const s3d::String& key, s3d::String message)
    {
        m_table[category][key] = std::move(message);
    }
    const s3d::String& abyss::Msg::MessageTable::get(const Label& label)
    {
        return m_table[label.category][label.key];
    }
}

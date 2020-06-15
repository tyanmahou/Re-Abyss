#include "KeyFlagsModel.hpp"
#include <Siv3D.hpp>

namespace abyss
{
    bool KeyFlagsModel::add(const s3d::String& key, SaveLevel level)
    {
        if (this->isContain(key)) {
            if (static_cast<s3d::int32>(m_flags[key]) >= static_cast<s3d::int32>(level)) {
                return false;
            }
        }
        m_flags[key] = level;
        return true;
    }
    bool KeyFlagsModel::isContain(const s3d::String& key) const
    {
        return m_flags.find(key) != m_flags.end();
    }
    void KeyFlagsModel::clear(SaveLevel level)
    {
        for (auto it = m_flags.begin(); it != m_flags.end();) {
            if (static_cast<s3d::int32>(it->second) <= static_cast<s3d::int32>(level)) {
                it = m_flags.erase(it);
            }else{
                ++it;
            }
        }
    }
}

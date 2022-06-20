#include <abyss/modules/Temporary/TempFrag/TempFlags.hpp>

#include <Siv3D.hpp>

namespace abyss
{
    bool TempFlags::add(const TempKey& key, TempLevel level)
    {
        for (auto&& pair : m_flags) {
            auto l = pair.first;
            auto& sets = m_flags[l];

            if (sets.find(key) != sets.end()) {
                if (static_cast<s3d::int32>(l) >= static_cast<s3d::int32>(level)) {
                    return false;
                } else {
                    sets.erase(key);
                    break;
                }
            }
        }
        m_flags[level].insert(key);
        return true;
    }
    bool TempFlags::isContain(const TempKey& key) const
    {
        for (const auto& [level, sets] : m_flags) {
            if (sets.find(key) != sets.end()) {
                return true;
            }
        }
        return false;
    }
    void TempFlags::clear(TempLevel level)
    {
        for (auto&& pair : m_flags) {
            auto l = pair.first;
            if (static_cast<s3d::int32>(l) <= static_cast<s3d::int32>(level)) {
                m_flags[l].clear();
            }
        }
    }
}

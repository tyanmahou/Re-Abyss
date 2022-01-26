#include <abyss/models/Temporary/TempFlag/TempFlagsModel.hpp>

#include <Siv3D.hpp>

namespace abyss
{
    bool TempFlagsModel::add(const TempKey& key, TempLevel level)
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
    bool TempFlagsModel::isContain(const TempKey& key) const
    {
        for (const auto& [level, sets] : m_flags) {
            if (sets.find(key) != sets.end()) {
                return true;
            }
        }
        return false;
    }
    void TempFlagsModel::clear(TempLevel level)
    {
        for (auto&& pair : m_flags) {
            auto l = pair.first;
            if (static_cast<s3d::int32>(l) <= static_cast<s3d::int32>(level)) {
                m_flags[l].clear();
            }
        }
    }
}

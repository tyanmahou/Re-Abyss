#include "SaveData.hpp"

namespace abyss
{
    bool SaveData::saveFlag(const s3d::String& key, SaveLevel level)
    {
        return m_flags.add(key, level);
    }

    bool SaveData::onFlag(const s3d::String& key) const
    {
        return m_flags.isContain(key);
    }

    void SaveData::setRestartInfo(const RestartInfoModel& info)
    {
        m_restartInfo = info;
    }

}

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

    void SaveData::reserveRestartId(s3d::int32 startId)
    {
        m_reservedRestartId = startId;
    }

    s3d::Optional<s3d::int32> SaveData::popReservedRestartId()
    {
        if (m_reservedRestartId) {
            auto ret = m_reservedRestartId;
            m_reservedRestartId = s3d::none;
            return ret;
        }
        return s3d::none;
    }

    void SaveData::setRestartInfo(const RestartInfoModel& info)
    {
        m_restartInfo = info;
    }

    const s3d::Optional<RestartInfoModel>& SaveData::getRestartInfo() const
    {
        return m_restartInfo;
    }

}

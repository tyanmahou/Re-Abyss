#include "TemporaryData.hpp"

namespace abyss
{
    bool TemporaryData::saveFlag(const TempKey& key, TempLevel level)
    {
        return m_flags.add(key, level);
    }

    bool TemporaryData::onFlag(const TempKey& key) const
    {
        return m_flags.isContain(key);
    }

    void TemporaryData::clearFlag(TempLevel level)
    {
        m_flags.clear(level);
    }

    void TemporaryData::reserveRestartId(s3d::int32 startId)
    {
        m_reservedRestartId = startId;
    }

    s3d::Optional<s3d::int32> TemporaryData::popReservedRestartId()
    {
        if (m_reservedRestartId) {
            s3d::Optional<s3d::int32> ret = std::move(m_reservedRestartId);
            m_reservedRestartId = s3d::none;
            return ret;
        }
        return s3d::none;
    }

    void TemporaryData::setRestartInfo(const RestartInfoModel& info)
    {
        m_restartInfo = info;
    }

    const s3d::Optional<RestartInfoModel>& TemporaryData::getRestartInfo() const
    {
        return m_restartInfo;
    }

}

#include <abyss/modules/Temporary/Temporary.hpp>
#include <abyss/modules/Temporary/TemporaryData.hpp>

namespace abyss
{
    Temporary::Temporary(const std::shared_ptr<TemporaryData>& tempData):
        m_tempData(tempData)
    {}
    bool Temporary::saveFlag(const TempKey& key, TempLevel level) const
    {
        return m_tempData->saveFlag(key, level);
    }

    bool Temporary::onFlag(const TempKey& key) const
    {
        return m_tempData->onFlag(key);
    }

    void Temporary::clearFlag(TempLevel level) const
    {
        m_tempData->clearFlag(level);
    }

    void Temporary::reserveRestartId(s3d::int32 startId) const
    {
        m_tempData->reserveRestartId(startId);
    }

    s3d::Optional<s3d::int32> Temporary::popReservedRestartId() const
    {
        return m_tempData->popReservedRestartId();
    }

    void Temporary::setRestartInfo(s3d::int32 startId, const s3d::Optional<Sound::SoundLabel>& bgm) const
    {
        RestartInfo info;
        info.setStartId(startId);
        info.setBgm(bgm);
        this->setRestartInfo(info);
    }

    void Temporary::setRestartInfo(const RestartInfo & info) const
    {
        m_tempData->setRestartInfo(info);
    }

    const s3d::Optional<RestartInfo>& Temporary::getRestartInfo() const
    {
        return m_tempData->getRestartInfo();
    }

    s3d::Optional<s3d::int32> Temporary::getRestartId() const
    {
        if (auto&& info = this->getRestartInfo()) {
            return info->getStartId();
        }
        return s3d::none;
    }

    s3d::Optional<Sound::SoundLabel> Temporary::getRestartBgm() const
    {
        if (auto&& info = this->getRestartInfo()) {
            return info->getBgm();
        }
        return s3d::none;
    }

}

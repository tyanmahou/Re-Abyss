#include "Save.hpp"
#include "SaveData.hpp"

namespace abyss
{
    Save::Save():
        m_saveData(std::make_shared<SaveData>())
    {}
    bool Save::saveFlag(const s3d::String& key, SaveLevel level) const
    {
        return m_saveData->saveFlag(key, level);
    }

    bool Save::onFlag(const s3d::String & key) const
    {
        return m_saveData->onFlag(key);
    }

    void Save::reserveRestartId(s3d::int32 startId) const
    {
        m_saveData->reserveRestartId(startId);
    }

    s3d::Optional<s3d::int32> Save::popReservedRestartId() const
    {
        return m_saveData->popReservedRestartId();
    }

    void Save::setRestartInfo(s3d::int32 startId, const s3d::Optional<s3d::String>& bgm) const
    {
        RestartInfoModel info;
        info.setStartId(startId);
        info.setBgm(bgm);
        this->setRestartInfo(info);
    }

    void Save::setRestartInfo(const RestartInfoModel & info) const
    {
        m_saveData->setRestartInfo(info);
    }

    const s3d::Optional<RestartInfoModel>& Save::getRestartInfo() const
    {
        return m_saveData->getRestartInfo();
    }

    s3d::Optional<s3d::int32> Save::getRestartId() const
    {
        if (auto info = this->getRestartInfo()) {
            return info->getStartId();
        }
        return s3d::none;
    }

    s3d::Optional<s3d::String> Save::getRestartBgm() const
    {
        if (auto info = this->getRestartInfo()) {
            return info->getBgm();
        }
        return s3d::none;
    }

    void Save::setSaveData(const std::shared_ptr<SaveData>& saveData)
    {
        m_saveData = saveData;
    }

}

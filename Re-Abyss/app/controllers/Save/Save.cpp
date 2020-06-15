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

}

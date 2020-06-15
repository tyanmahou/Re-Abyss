#pragma once
#include <memory>
#include <Siv3D/Fwd.hpp>
#include <abyss/models/Save/KeyFlag/SaveLevel.hpp>
namespace abyss
{
    class SaveData;
    class RestartInfoModel;

    class Save
    {
        std::shared_ptr<SaveData> m_saveData;
    public:
        Save();

        bool saveFlag(const s3d::String& key, SaveLevel level = SaveLevel::Room) const;
        bool saveFlagRoom(const s3d::String& key) const
        {
            return this->saveFlag(key, SaveLevel::Room);
        }
        bool saveFlagRestart(const s3d::String& key) const
        {
            return this->saveFlag(key, SaveLevel::Restart);
        }
        bool saveFlagNever(const s3d::String& key) const
        {
            return this->saveFlag(key, SaveLevel::Never);
        }

        bool onFlag(const s3d::String& key) const;

        void setRestartInfo(s3d::int32 startId, const s3d::Optional<s3d::String>& bgm) const;
        void setRestartInfo(const RestartInfoModel& info) const;
    };
}
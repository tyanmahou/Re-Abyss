#pragma once
#include <abyss/models/Save/RestartInfo/RestartInfoModel.hpp>
#include <abyss/models/Save/KeyFlag/KeyFlagsModel.hpp>

namespace abyss
{
    class SaveData
    {
        RestartInfoModel m_restartInfo;
        KeyFlagsModel m_flags;
    public:
        bool saveFlag(const s3d::String& key, SaveLevel level);
        bool onFlag(const s3d::String& key)const;

        void setRestartInfo(const RestartInfoModel& info);
    };
}
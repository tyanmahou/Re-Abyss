#pragma once
#include <abyss/models/Save/RestartInfo/RestartInfoModel.hpp>
#include <abyss/models/Save/KeyFlag/KeyFlagsModel.hpp>

namespace abyss
{
    class SaveData
    {
        s3d::Optional<RestartInfoModel> m_restartInfo;
        s3d::Optional<s3d::int32> m_reservedRestartId;
        KeyFlagsModel m_flags;
    public:
        bool saveFlag(const s3d::String& key, SaveLevel level);
        bool onFlag(const s3d::String& key)const;

        /// <summary>
        /// リスタートIdを予約
        /// </summary>
        /// <param name="startId"></param>
        void reserveRestartId(s3d::int32 startId);

        /// <summary>
        /// 予約したリスタートIdをポップ
        /// </summary>
        /// <returns></returns>
        s3d::Optional<s3d::int32> popReservedRestartId();

        void setRestartInfo(const RestartInfoModel& info);
        const s3d::Optional<RestartInfoModel>& getRestartInfo() const;
    };
}
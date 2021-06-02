#pragma once
#include <abyss/models/Temporary/RestartInfo/RestartInfoModel.hpp>
#include <abyss/models/Temporary/TempFlag/TempFlagsModel.hpp>

namespace abyss
{
    class TemporaryData
    {
        s3d::Optional<RestartInfoModel> m_restartInfo;
        s3d::Optional<s3d::int32> m_reservedRestartId;
        TempFlagsModel m_flags;
    public:
        bool saveFlag(const TempKey& key, TempLevel level);
        bool onFlag(const TempKey& key)const;
        void clearFlag(TempLevel level);

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
#pragma once
#include <abyss/modules/Temporary/RestartInfo/RestartInfo.hpp>
#include <abyss/modules/Temporary/TempFrag/TempFlags.hpp>

namespace abyss
{
    class TemporaryData
    {
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

        void setRestartInfo(const RestartInfo& info);
        const s3d::Optional<RestartInfo>& getRestartInfo() const;

    private:
        s3d::Optional<RestartInfo> m_restartInfo;
        s3d::Optional<s3d::int32> m_reservedRestartId;
        TempFlags m_flags;
    };
}

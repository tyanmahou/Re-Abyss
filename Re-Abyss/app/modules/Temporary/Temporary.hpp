#pragma once
#include <memory>
#include <Siv3D/Fwd.hpp>
#include <abyss/types/Temporary/TempKey.hpp>
#include <abyss/types/Temporary/TempLevel.hpp>

namespace abyss
{
    class TemporaryData;
    class RestartInfoModel;

    class Temporary
    {
        std::shared_ptr<TemporaryData> m_tempData;
    public:
        Temporary();

        bool saveFlag(const TempKey& key, TempLevel level = TempLevel::Restart) const;
        bool saveFlagRoom(const TempKey& key) const
        {
            return this->saveFlag(key, TempLevel::Room);
        }
        bool saveFlagRestart(const TempKey& key) const
        {
            return this->saveFlag(key, TempLevel::Restart);
        }
        bool saveFlagExit(const TempKey& key) const
        {
            return this->saveFlag(key, TempLevel::Exit);
        }
        bool saveFlagNever(const TempKey& key) const
        {
            return this->saveFlag(key, TempLevel::Never);
        }

        bool onFlag(const TempKey& key) const;

        void clearFlag(TempLevel level) const;

        /// <summary>
        /// リスタートIdを予約
        /// </summary>
        /// <param name="startId"></param>
        void reserveRestartId(s3d::int32 startId) const;

        /// <summary>
        /// 予約したリスタートIdをポップ
        /// </summary>
        /// <returns></returns>
        s3d::Optional<s3d::int32> popReservedRestartId() const;

        void setRestartInfo(s3d::int32 startId, const s3d::Optional<s3d::String>& bgm) const;
        void setRestartInfo(const RestartInfoModel& info) const;
        const s3d::Optional<RestartInfoModel>& getRestartInfo() const;
        s3d::Optional<s3d::int32> getRestartId()const;
        s3d::Optional<s3d::String> getRestartBgm()const;

        void setTemporaryData(const std::shared_ptr<TemporaryData>& tempData);
    };
}
#pragma once
#include <memory>
#include <Siv3D/Optional.hpp>
#include <abyss/modules/Temporary/TempFrag/TempKey.hpp>
#include <abyss/modules/Temporary/TempFrag/TempLevel.hpp>
#include <abyss/modules/Sound/SoundBank/SoundLabel.hpp>
#include <Emaject.hpp>

namespace abyss
{
    class TemporaryData;
    class RestartInfo;

    /// <summary>
    /// 一時的なデータ置き場
    /// </summary>
    class Temporary
    {
    public:
        INJECT_CTOR(Temporary(const std::shared_ptr<TemporaryData>& tempData));

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

        void setRestartInfo(s3d::int32 startId, const s3d::Optional<Sound::SoundLabel> & bgm) const;
        void setRestartInfo(const RestartInfo& info) const;
        const s3d::Optional<RestartInfo>& getRestartInfo() const;
        s3d::Optional<s3d::int32> getRestartId()const;
        s3d::Optional<Sound::SoundLabel> getRestartBgm()const;
    private:
        std::shared_ptr<TemporaryData> m_tempData;
    };
}

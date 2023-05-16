#pragma once
#include <Siv3D/String.hpp>
#include <Siv3D/Audio.hpp>
#include <abyss/modules/Sound/SceneSound.hpp>

namespace abyss
{
    /// <summary>
    /// サウンド関連
    /// </summary>
    class Sound
    {
    public:
        Sound(SceneSound* pSceneSound);
        ~Sound();
        void play(const s3d::String& path, const s3d::Duration& sec = 2s);

        void stop(const s3d::Duration& sec = 2s);

        void stash(const s3d::Duration& sec = 2s);
        void stashPop(const s3d::Duration& sec = 2s);

        void release();

        const s3d::Optional<s3d::String>& currentBgmPath()const;

        void setBusVolume(s3d::MixBus busIndex, double volume);
        void fadeBusVolume(s3d::MixBus busIndex, double volume, const s3d::Duration& time);

        void setBgmVolume(double volume);
        void fadeBgmVolume(double volume, const s3d::Duration& time);
    private:
        SceneSound* m_pSceneSound = nullptr;
    };
}

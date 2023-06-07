#pragma once
#include <Siv3D/String.hpp>
#include <Siv3D/Audio.hpp>
#include <abyss/modules/Sound/SceneSound.hpp>

namespace abyss::Sound
{
    /// <summary>
    /// サウンド関連
    /// </summary>
    class Sounds
    {
    public:
        Sounds(SceneSound* pSceneSound);
        ~Sounds();
        void play(const s3d::String& path, const s3d::Duration& sec = 0.2s);
        void play(const SoundLabel& label, const s3d::Duration& sec = 0.2s);

        void stop(const s3d::Duration& sec = 0.2s);

        void stash(const s3d::Duration& sec = 0.2s);
        void stashPop(const s3d::Duration& sec = 0.2s);

        void release();

        const s3d::Optional<s3d::String>& currentBgmPath()const;

        void setBgmVolume(double volume);
        void setBgmVolume(double volume, const s3d::Duration& time);

        void playSe(const s3d::String& path);

        void setMasterVolume(double volume);
        void setMasterVolume(double volume, const s3d::Duration& time);

        BackGroundMusic* bgm() const;
        SoundEffects* se() const;
    private:
        SceneSound* m_pSceneSound = nullptr;
    };
}

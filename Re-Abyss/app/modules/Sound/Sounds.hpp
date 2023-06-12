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
        void play(const SoundLabel& label, const s3d::Duration& sec = 0.2s);

        void stop(const s3d::Duration& sec = 0.2s);

        void stash(const s3d::Duration& sec = 0.2s);
        void stashPop(const s3d::Duration& sec = 0.2s);

        void release();

        const s3d::Optional<SoundLabel>& currentBgmLabel()const;

        void setBgmVolume(double volume);
        void setBgmVolume(double volume, const s3d::Duration& time);

        void playSe(const SoundLabel& label);

        void setMasterVolume(double volume);
        void setMasterVolume(double volume, const s3d::Duration& time);

        BackGroundMusic* bgm() const;
        SoundEffects* se() const;
        AudioSetting setting(const SoundLabel& label) const;
        s3d::Audio load(const SoundLabel& label, Resource::Assets* pAssets = Resource::Assets::Main()) const;
    private:
        SceneSound* m_pSceneSound = nullptr;
    };
}

#pragma once
#include <stack>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/modules/Sound/SoundBank/ISoundBank.hpp>
#include <Siv3D/String.hpp>
#include <Siv3D/Audio.hpp>

namespace abyss::Sound
{
    /// <summary>
    /// BGM制御
    /// </summary>
    class BackGroundMusic
    {
    public:
        BackGroundMusic(ISoundBank* pSoundBank, Resource::Assets* pAssets = Resource::Assets::NoRelease());

        /// <summary>
        /// 再生
        /// </summary>
        /// <param name="path"></param>
        /// <param name="sec"></param>
        void play(const SoundLabel& label, const s3d::Duration& sec = 0.2s);

        /// <summary>
        /// 停止
        /// </summary>
        /// <param name="sec"></param>
        void stop(const s3d::Duration& sec = 0.2s);

        /// <summary>
        /// リリース
        /// </summary>
        void release();

        const s3d::Optional<SoundLabel>& getCurrentLabel()const
        {
            return m_currentLabel;
        }

        /// <summary>
        /// 一時退避
        /// </summary>
        void stash(const s3d::Duration& sec = 2s);
        void stashPop(const s3d::Duration& sec = 2s);

        void setVolume(double volume);
        void setVolume(double volume, const s3d::Duration& time);
    private:
        ISoundBank* m_pSoundBank;
        Resource::Assets* m_pAssets;

        s3d::Audio m_prev;
        s3d::Audio m_current;
        s3d::Optional<SoundLabel> m_currentLabel;
        std::stack<SoundLabel> m_stash;
    };
}

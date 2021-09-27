#pragma once
#include <Siv3D/String.hpp>
#include <Siv3D/Audio.hpp>
#include <abyss/modules/Sound/BackGroundMusic.hpp>

namespace abyss
{
    /// <summary>
    /// サウンド関連
    /// </summary>
    class Sound
    {
    public:
        Sound() = default;
        ~Sound();
        void play(const s3d::String& path, const s3d::Duration& sec = 2s);

        void stop(const s3d::Duration& sec = 2s);

        void release();

        const s3d::Optional<s3d::String>& currentBgmPath()const;
    private:
        BackGroundMusic m_bgm;
    };
}
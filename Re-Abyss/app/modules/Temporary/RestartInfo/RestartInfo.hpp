#pragma once
#include <abyss/values/Sound/SoundLabel.hpp>
#include <Siv3D/Fwd.hpp>
#include <Siv3D/Optional.hpp>

namespace abyss
{
    class RestartInfo
    {
    public:
        s3d::int32 getStartId() const
        {
            return m_startId;
        }
        void setStartId(s3d::int32 startId)
        {
            m_startId = startId;
        }
        const s3d::Optional<Sound::SoundLabel>& getBgm() const
        {
            return m_bgm;
        }
        void setBgm(const Sound::SoundLabel& bgm)
        {
            m_bgm = bgm;
        }
        void setBgm(const s3d::Optional<Sound::SoundLabel>& bgm)
        {
            m_bgm = bgm;
        }
    private:
        s3d::int32 m_startId = 0;
        s3d::Optional<Sound::SoundLabel> m_bgm;
    };
}

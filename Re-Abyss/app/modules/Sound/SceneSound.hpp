#pragma once
#include <abyss/modules/Sound/BackGroundMusic.hpp>

namespace abyss
{
    class SceneSound
    {
    public:
        void play(const s3d::String& path, const s3d::Duration& sec = 0.2s);

        void stop(const s3d::Duration& sec = 0.2s);

        void stash(const s3d::Duration& sec = 0.2s);
        void stashPop(const s3d::Duration& sec = 0.2s);

        void release();

        const s3d::Optional<s3d::String>& currentBgmPath()const;
    private:
        BackGroundMusic m_bgm;
    };
}

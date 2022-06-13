#pragma once
#include <abyss/modules/Sound/BackGroundMusic.hpp>

namespace abyss
{
    class BgmBridge
    {
    public:
        void set(const BackGroundMusic& bgm)
        {
            m_bgm = bgm;
        }
        s3d::Optional<BackGroundMusic> pop()
        {
            auto bgm = std::move(m_bgm);
            m_bgm.reset();
            return bgm;
        }
        void reset()
        {
            m_bgm.reset();
        }
    private:
        s3d::Optional<BackGroundMusic> m_bgm;
    };
}

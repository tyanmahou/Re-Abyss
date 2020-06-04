#pragma once
#include <Siv3D/String.hpp>
#include <Siv3D/Audio.hpp>
#include <abyss/commons/Fwd.hpp>
namespace abyss
{
    class Sound
    {
        s3d::Audio m_prev;
        s3d::Audio m_current;
        s3d::String m_currentPath;

    public:
        Sound() = default;
        ~Sound();
        void play(const s3d::String& path, const s3d::Duration& sec = 1s);

        void stop(const Duration& sec) const;

        void release() const;

    };
}
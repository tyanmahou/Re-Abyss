#pragma once
#include <Siv3D/String.hpp>

namespace abyss::Sound
{
    class SoundLabel
    {
    public:
        SoundLabel() = default;
        SoundLabel(const s3d::String& key) :
            m_key(key)
        {}
        const s3d::String& key() const
        {
            return m_key;
        }

        bool operator==(const Sound::SoundLabel& other)const = default;
    private:
        s3d::String m_key;
    };
}

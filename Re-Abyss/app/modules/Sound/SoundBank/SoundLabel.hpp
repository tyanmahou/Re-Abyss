#pragma once
#include <Siv3D/StringView.hpp>

namespace abyss::Sound
{
    class SoundLabel
    {
    public:
        constexpr SoundLabel(s3d::StringView key) :
            m_key(key)
        {}
        s3d::StringView key() const
        {
            return m_key;
        }
    private:
        s3d::StringView m_key;
    };
}

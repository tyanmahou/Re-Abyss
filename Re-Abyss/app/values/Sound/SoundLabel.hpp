#pragma once
#include <Siv3D/String.hpp>

namespace abyss::Sound
{
    class SoundLabel
    {
    public:
        SoundLabel() = default;
        explicit SoundLabel(const s3d::String& key) :
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
namespace std
{
    template<>
    struct hash<abyss::Sound::SoundLabel>
    {
        [[nodiscard]] std::size_t operator()(const abyss::Sound::SoundLabel& key) const
        {
            return std::hash<s3d::String>{}(key.key());
        }
    };
}

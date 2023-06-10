#pragma once
#include <Siv3D/Audio.hpp>
#include <Siv3D/HashTable.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/modules/Sound/SoundBank/ISoundBank.hpp>

namespace abyss::Sound
{
    class SeCaches
    {
    public:
        s3d::Audio load(Resource::Assets* pAssets, ISoundBank* pSoundBank, const SoundLabel& label);
    private:
        s3d::HashTable<SoundLabel, s3d::Audio> m_cache;
    };
}

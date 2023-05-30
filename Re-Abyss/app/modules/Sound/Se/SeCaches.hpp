#pragma once
#include <Siv3D/Audio.hpp>
#include <Siv3D/HashTable.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss::Sound
{
    class SeCaches
    {
    public:
        s3d::Audio load(Resource::Assets* pAssets, const s3d::String& path);
    private:
        s3d::HashTable<s3d::FilePath, s3d::Audio> m_cache;
    };
}

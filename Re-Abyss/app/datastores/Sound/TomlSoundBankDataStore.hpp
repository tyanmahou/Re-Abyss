#pragma once
#include <abyss/datastores/Sound/base/ISoundBankDataStore.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss::Sound
{
    class TomlSoundBankDataStore : ISoundBankDataStore
    {
    public:
        TomlSoundBankDataStore(const s3d::FilePath& path, Resource::Assets* pAsset);

        s3d::HashTable<s3d::String, AudioSetting> select() const override;
    private:
        s3d::TOMLValue m_rawData;
    };
}

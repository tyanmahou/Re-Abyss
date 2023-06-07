#pragma once
#include <abyss/datastores/Sound/base/ISoundBankDataStore.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss::Sound
{
    class CSVSoundBankDataStore : ISoundBankDataStore
    {
    public:
        CSVSoundBankDataStore(const s3d::FilePath& path, Resource::Assets* pAsset);

        s3d::HashTable<s3d::String, AudioSetting> select() const override;
    private:
        s3d::CSV m_csv;
    };
}

#include <abyss/datastores/Sound/TomlSoundBankDataStore.hpp>

namespace abyss::Sound
{
    TomlSoundBankDataStore::TomlSoundBankDataStore(const s3d::FilePath& path, Resource::Assets* pAsset)
    {
        m_rawData = pAsset->loadToml(path, Path::Root);
    }
    s3d::HashTable<s3d::String, AudioSetting> abyss::Sound::TomlSoundBankDataStore::select() const
    {
        // TODO 実装
        return {};
    }
}

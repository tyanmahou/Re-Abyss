#include <abyss/datastores/Sound/TomlSoundBankDataStore.hpp>
#include <abyss/utils/AudioSetting/AudioSettingReader.hpp>

namespace abyss::Sound
{
    TomlSoundBankDataStore::TomlSoundBankDataStore(const s3d::FilePath& path, Resource::Assets* pAsset)
    {
        m_rawData = pAsset->loadToml(path, Path::Root);
    }
    s3d::HashTable<s3d::String, AudioSetting> TomlSoundBankDataStore::select() const
    {
        s3d::HashTable<s3d::String, AudioSetting> ret{};

        AudioSettingReader reader{};
        for (auto&& toml : m_rawData.tableView()) {
            ret.emplace(toml.name, reader.load(toml.value));
        }

        return ret;
    }
}

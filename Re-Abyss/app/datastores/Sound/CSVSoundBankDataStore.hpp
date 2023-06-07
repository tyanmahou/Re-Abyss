#pragma once
#include <abyss/datastores/Sound/base/ISoundBankDataStore.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <Emaject.hpp>
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

    struct CSVSoundBankDataStoreInstaller final : emaject::IInstaller
    {
        CSVSoundBankDataStoreInstaller(const s3d::FilePath& path, Resource::Assets* pAssets = Resource::Assets::Main()) :
            m_path(path),
            m_pAssets(pAssets)
        {
        }
        void onBinding(emaject::Container* container) const override
        {
            container->bind<ISoundBankDataStore>()
                .to<CSVSoundBankDataStore>()
                .withArgs(m_path, m_pAssets)
                .asCached();
        }
    private:
        s3d::FilePath m_path;
        Resource::Assets* m_pAssets = nullptr;
    };
}

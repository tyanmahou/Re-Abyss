#pragma once
#include <abyss/datastores/Adv/base/IProjectDataStore.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <Emaject.hpp>

namespace abyss::Adv
{
    class TomlProjectDataStore final : public IProjectDataStore
    {
        struct Project
        {
            [[TOML_BIND(chara, "Chara")]]
            s3d::Array<CharaEntity> chara;
        };
    public:
        TomlProjectDataStore(const s3d::FilePath& path, Resource::Assets* pAssets);
    public:
        s3d::Array<CharaEntity> selectCharas() const override;
    private:
        Project m_project;
    };

    struct TomlProjectDataStoreInstaller final: emaject::IInstaller
    {
        TomlProjectDataStoreInstaller(const s3d::FilePath& path, Resource::Assets* pAssets = Resource::Assets::Main()) :
            m_path(path),
            m_pAssets(pAssets)
        {
        }
        void onBinding(emaject::Container* container) const override
        {
            container->bind<IProjectDataStore>()
                .to<TomlProjectDataStore>()
                .withArgs(m_path, m_pAssets)
                .asCached();
        }
    private:
        s3d::FilePath m_path;
        Resource::Assets* m_pAssets = nullptr;
    };
}

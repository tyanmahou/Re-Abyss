#include <abyss/datastores/Adv/TomlProjectDataStore.hpp>

namespace abyss::Adv
{
    TomlProjectDataStore::TomlProjectDataStore(const s3d::FilePath& path, Resource::Assets* pAssets)
    {
        m_project = pAssets->loadToml<Project>(path, U"");
    }
    s3d::Array<CharaEntity> TomlProjectDataStore::selectCharas() const
    {
        return m_project.chara;
    }
}

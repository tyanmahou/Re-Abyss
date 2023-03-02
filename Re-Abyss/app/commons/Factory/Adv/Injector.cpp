#include <abyss/commons/Factory/Adv/Injector.hpp>

#include <abyss/commons/Path.hpp>
#include <abyss/datastores/Adv/TomlProjectDataStore.hpp>
#include <abyss/services/Adv/ProjectService.hpp>

namespace abyss::Factory::Adv
{
    emaject::Injector Injector()
    {
        return Injector(Path::AdvPath + U"project.toml", Resource::Assets::Temporray());
    }
    emaject::Injector Injector(const s3d::FilePath& path, Resource::Assets* pAssets)
    {
        using namespace abyss::Adv;

        emaject::Injector injector;
        injector
            // datastore
            .install<TomlProjectDataStoreInstaller>(path, pAssets)
            // service
            .install<ProjectServiceInstaller>()
            ;
        return injector;
    }
}

#include <abyss/commons/Factory/Adv/Injector.hpp>

#include <abyss/commons/Path.hpp>
#include <abyss/datastores/Adv/TomlProjectDataStore.hpp>
#include <abyss/services/Adv/ProjectService.hpp>

namespace abyss::Factory::Adv
{
    emaject::Injector Injector()
    {
        emaject::Injector injector;
        Install(injector);
        return injector;
    }
    emaject::Injector Injector(const s3d::FilePath& path, Resource::Assets* pAssets)
    {
        using namespace abyss::Adv;

        emaject::Injector injector;
        Install(injector, path, pAssets);
        return injector;
    }

    void Install(emaject::Injector& injector)
    {
        Install(injector, Path::AdvPath + U"project.toml", Resource::Assets::Temporray());
    }
    void Install(emaject::Injector& injector, const s3d::FilePath& path, Resource::Assets* pAssets)
    {
        using namespace abyss::Adv;
        injector
            // datastore
            .install<TomlProjectDataStoreInstaller>(path, pAssets)
            // service
            .install<ProjectServiceInstaller>()
            ;
    }
}

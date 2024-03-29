#if ABYSS_DEVELOP
#include <abyss/commons/Factory/Project/Injector.hpp>

#include <abyss/datastores/Devs/Project/GitHubDataStore.hpp>
#include <abyss/services/Devs/Project/ProjectService.hpp>

namespace abyss::Factory::Project
{
    emaject::Injector Injector()
    {
        using namespace abyss::Devs::Project;

        emaject::Injector injector;
        Install(injector);
        return injector;
    }
    void Install(emaject::Injector& injector)
    {
        using namespace abyss::Devs::Project;
        injector
            // datastore
            .install<GitHubDataStoreInstaller>()
            // service
            .install<ProjectServiceInstaller>()
            ;
    }
}
#endif

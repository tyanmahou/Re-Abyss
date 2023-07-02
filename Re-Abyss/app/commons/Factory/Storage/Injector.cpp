#include <abyss/commons/Factory/Storage/Injector.hpp>

#include <abyss/datastores/User/DBUserDataStore.hpp>
#include <abyss/services/User/UserService.hpp>

namespace abyss::Factory::Storage
{
    emaject::Injector Injector()
    {
        using namespace abyss::User;

        emaject::Injector injector;
        Install(injector);
        return injector;
    }
    void Install(emaject::Injector& injector)
    {
        using namespace abyss::User;
        injector
            // other
            .install<DBInstaller>()
            // datastore
            .install<DBUserDataStoreInataller>()
            // service
            .install<UserServiceInstaller>()
            ;
    }
}

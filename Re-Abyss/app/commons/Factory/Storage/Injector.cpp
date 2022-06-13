#include <abyss/commons/Factory/Storage/Injector.hpp>

#include <abyss/datastores/User/DBUserDataStore.hpp>
#include <abyss/services/User/UserService.hpp>

namespace abyss::Factory::Storage
{
    emaject::Injector Injector()
    {
        using namespace abyss::User;

        emaject::Injector injector;
        injector
            // other
            .install<DBInstaller>()
            // datastore
            .install<DBUserDataStoreInataller>()
            // service
            .install<UserServiceInstaller>()
            ;
        return injector;
    }
}

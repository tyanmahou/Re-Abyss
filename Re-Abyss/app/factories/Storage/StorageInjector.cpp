#include <abyss/factories/Storage/StorageInjector.hpp>

#include <abyss/datastores/User/DBUserDataStore.hpp>
#include <abyss/services/User/UserService.hpp>

emaject::Injector abyss::Factory::Storage::Injector()
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

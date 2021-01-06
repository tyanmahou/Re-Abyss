#include "MigrationInjector.hpp"
#include <abyss/datastores/Migration/DBMigrationDataStore.hpp>
#include <abyss/datastores/MigrationVersion/DBMigrationVersionDataStore.hpp>

#include <abyss/services/Migration/DBMigrationService.hpp>

namespace abyss::Factory::Migration
{
    emaject::Injector Injector()
    {
        using namespace abyss::User;

        emaject::Injector injector;
        injector
            // other
            .install<DBInstaller>()
            // datastore
            .install<DBMigrationDataStoreInataller>()
            .install<DBMigrationVersionDataStoreInataller>()
            // service
            .install<DBMigrationServiceInstaller>()
            ;
        return injector;
    }
}

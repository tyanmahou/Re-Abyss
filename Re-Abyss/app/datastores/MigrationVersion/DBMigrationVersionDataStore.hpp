#pragma once
#include <abyss/datastores/MigrationVersion/base/IMigrationVersionDataStore.hpp>
#include <abyss/datastores/base/DBDataStore.hpp>

namespace abyss::User
{
    class DBMigrationVersionDataStore :
        public IMigrationVersionDataStore,
        public DBDataStore
    {
    public:
        using DBDataStore::DBDataStore;

        bool create() const override;

        s3d::int64 selectCurrentVersion()const override;
        bool update(const s3d::Array<s3d::int64>& versions)const override;
        bool erase(s3d::int64 versionId)const override;
    };

    using DBMigrationVersionDataStoreInataller = DBDataStoreInataller<IMigrationVersionDataStore, DBMigrationVersionDataStore>;
}
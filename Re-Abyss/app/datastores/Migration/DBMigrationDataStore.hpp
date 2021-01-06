#pragma once
#include <abyss/datastores/Migration/base/IMigration.hpp>
#include <abyss/datastores/Migration/base/IMigrationDataStore.hpp>
#include <abyss/datastores/base/DBDataStore.hpp>

namespace abyss::User
{
    class DBMigrationDataStore : 
        public IMigrationDataStore,
        public DBDataStore
    {
    public:
        DBMigrationDataStore(const std::shared_ptr<s3dsql::SQLite3>& db);

        s3d::Array<s3d::int32> versionIds() const override;

        void up(s3d::int32 versionId) const override;
        void down(s3d::int32 versionId) const override;
    private:
        s3d::HashTable<s3d::int32, std::function<std::shared_ptr<IMigration>()>> m_migrations;
    };
    using DBMigrationDataStoreInataller = DBDataStoreInataller<IMigrationDataStore, DBMigrationDataStore>;
}
#pragma once
#include <abyss/datastores/Migration/base/IMigration.hpp>
#include <abyss/datastores/Migration/base/IMigrationDataStore.hpp>
#include <abyss/datastores/base/DBDataStore.hpp>

namespace abyss::User
{
    class MigrationDataStore : 
        public IMigrationDataStore
    {
    public:
        MigrationDataStore();

        s3d::Array<s3d::int32> versionIds() const override;

        void up(s3d::int32 versionId) const override;
        void down(s3d::int32 versionId) const override;
    private:
        s3d::HashTable<s3d::int32, std::function<std::shared_ptr<Migrations::IMigration>()>> m_migrations;
    };
    using MigrationDataStoreInataller = DBDataStoreInataller<IMigrationDataStore, MigrationDataStore>;
}
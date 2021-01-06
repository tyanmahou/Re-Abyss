#include "DBMigrationDataStore.hpp"

// Migrations
#include "DB/2021010701_CreateUserTable.hpp"

namespace abyss::User
{
    DBMigrationDataStore::DBMigrationDataStore(const std::shared_ptr<s3dsql::SQLite3>& db):
        DBDataStore(db)
    {
#define MIGRATION_ADD(version) m_migrations[version] = [d = *db] {return std::make_shared<Migrations::DBMigration<version>>(d); }

        MIGRATION_ADD(2021010701);

#undef MIGRATION_ADD
    }
    s3d::Array<s3d::int32> DBMigrationDataStore::versionIds() const
    {
        s3d::Array<s3d::int32> ret;
        for (auto&& m : m_migrations) {
            ret << m.first;
        }
        return ret.sorted();
    }
    void DBMigrationDataStore::up(s3d::int32 versionId) const
    {
        m_migrations.at(versionId)()->up();
    }
    void DBMigrationDataStore::down(s3d::int32 versionId) const
    {
        m_migrations.at(versionId)()->down();
    }
}

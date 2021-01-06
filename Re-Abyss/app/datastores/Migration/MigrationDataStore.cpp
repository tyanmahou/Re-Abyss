#include "MigrationDataStore.hpp"

// Migrations
#include "Migrations/2021010701_CreateUserTable.hpp"

namespace abyss::User
{
    MigrationDataStore::MigrationDataStore()
    {
#define MIGRATION_ADD(version) m_migrations[version] = [] {return std::make_shared<Migrations::Migration<version>>(); }

        MIGRATION_ADD(2021010701);

#undef MIGRATION_ADD
    }
    s3d::Array<s3d::int32> MigrationDataStore::versionIds() const
    {
        s3d::Array<s3d::int32> ret;
        for (auto&& m : m_migrations) {
            ret << m.first;
        }
        return ret.sorted();
    }
    void MigrationDataStore::up(s3d::int32 versionId) const
    {
        m_migrations.at(versionId)()->up();
    }
    void MigrationDataStore::down(s3d::int32 versionId) const
    {
        m_migrations.at(versionId)()->down();
    }
}

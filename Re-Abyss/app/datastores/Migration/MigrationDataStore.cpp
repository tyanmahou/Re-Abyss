#include <abyss/datastores/Migration/MigrationDataStore.hpp>
#include <abyss/utils/Migration/Migration.hpp>

namespace abyss::User
{
    MigrationDataStore::MigrationDataStore()
    {
    }
    s3d::Array<s3d::int64> MigrationDataStore::versionIds() const
    {
        return Migration::MigrationHundler::Versions();
    }
    s3d::Array<s3d::int64> MigrationDataStore::updateVersionIds(s3d::int64 currentVersionId) const
    {
        return Migration::MigrationHundler::UpdateVersions(currentVersionId);
    }
    void MigrationDataStore::up(s3d::int64 versionId) const
    {
        Migration::MigrationHundler::Get(versionId)->up();
    }
    void MigrationDataStore::down(s3d::int64 versionId) const
    {
        Migration::MigrationHundler::Get(versionId)->down();
    }
}

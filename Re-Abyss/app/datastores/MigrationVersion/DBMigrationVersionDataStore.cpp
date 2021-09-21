#include "DBMigrationVersionDataStore.hpp"
#include <abyss/utils/DB/DBUtil.hpp>
#include <Siv3D.hpp>

namespace abyss::User
{
    bool DBMigrationVersionDataStore::create() const
    {
        StringView sql = U""
            "CREATE TABLE IF NOT EXISTS `migration_versions` ("
            "  `version_id` INTEGER PRIMARY KEY NOT NULL,"
            "  `created_at` TEXT DEFAULT(DATETIME('now', 'localtime')) NOT NULL"
            "); "
        ;
        m_db.exec(sql);
        return true;
    }
    s3d::int64 DBMigrationVersionDataStore::selectCurrentVersion() const
    {
        auto raw = m_db.fetchOne(U"SELECT MAX(version_id) as current_version FROM migration_versions;");
        if (!raw) {
            return 0;
        }
        return (*raw)[U"current_version"].getOr<s3d::int64>(0);
    }
    bool DBMigrationVersionDataStore::update(const s3d::Array<s3d::int64>& versions) const
    {
        if (versions.empty()) {
            return false;
        }
        String sql = U""
            "INSERT OR IGNORE INTO"
            "    migration_versions(version_id)"
            "VALUES"
            "    {}"
            ";"
        ;
        return DBUtil::ExecPlaceHolder<1>(m_db, sql, versions, [](auto& params, s3d::int64 value) {
            params << value;
        }) != 0;
    }
    bool DBMigrationVersionDataStore::erase(s3d::int64 versionId) const
    {
        StringView sql = U""
            "DELETE"
            "    migration_versions"
            "WHERE"
            "    `version_id` = :versionId"
            ";"
        ;

        s3dsql::DBValueMap params;
        params[U":versionId"] = versionId;

        return m_db.exec(sql, params) != 0;
    }
}

#include "Migration.hpp"

namespace abyss::Migration
{
    s3d::Array<s3d::int32> MigrationHundler::Versions()
    {
        s3d::Array<s3d::int32> ret;
        for (auto&& m : m_migrations) {
            ret << m.first;
        }
        return ret.sorted();
    }
    s3d::Array<s3d::int32> MigrationHundler::UpdateVersions(s3d::int32 currentVersion)
    {
        s3d::Array<s3d::int32> ret;
        for (auto&& m : m_migrations) {
            if (m.first > currentVersion) {
                // 現在のバージョンより上
                ret << m.first;
            }
        }
        return ret.sorted();
    }
    IMigration* MigrationHundler::Get(s3d::int32 version)
    {
        return m_migrations[version];
    }
}
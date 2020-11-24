#include "DBUserDataStore.hpp"

namespace abyss::User
{
    bool DBUserDataStore::create() const
    {
        s3d::String sql = U"";
        return m_db.exec(sql);
    }

    s3d::Array<UserEntity> DBUserDataStore::selectAll() const
    {
        return s3d::Array<UserEntity>();
    }

    s3d::Optional<UserEntity> DBUserDataStore::select(s3d::int32 userId) const
    {
        return s3d::Optional<UserEntity>();
    }

    bool DBUserDataStore::update(const UserEntity& entity) const
    {
        s3d::String sql = U"";
        return m_db.exec(sql);
    }

    bool DBUserDataStore::erase(s3d::int32 userId) const
    {
        s3d::String sql = U"";
        return m_db.exec(sql);
    }

}

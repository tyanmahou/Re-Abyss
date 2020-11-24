#include "DBUserDataStore.hpp"


namespace abyss::User
{
    bool DBUserDataStore::create() const
    {
        return false;
    }

    s3d::Array<UserEntity> DBUserDataStore::selectAll() const
    {
        return s3d::Array<UserEntity>();
    }

    s3d::Optional<UserEntity> DBUserDataStore::select(s3d::int32 userId) const
    {
        return s3d::Optional<UserEntity>();
    }

    void DBUserDataStore::update(const UserEntity& entity) const
    {}

}

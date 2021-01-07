#pragma once
#include <abyss/datastores/User/base/IUserDataStore.hpp>
#include <abyss/datastores/base/DBDataStore.hpp>

namespace abyss::User
{
    class DBUserDataStore :
        public DBDataStore,
        public IUserDataStore
    {
    public:
        using DBDataStore::DBDataStore;
        s3d::Array<UserEntity> selectAll()const final;
        s3d::Optional<UserEntity> select(s3d::int32 userId)const final;

        bool update(const UserEntity& entity)const final;
        bool erase(s3d::int32 userId)const final;
    };

    using DBUserDataStoreInataller = DBDataStoreInataller<IUserDataStore, DBUserDataStore>;

}
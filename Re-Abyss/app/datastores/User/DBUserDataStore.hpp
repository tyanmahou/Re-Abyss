#pragma once
#include <abyss/datastores/User/base/IUserDataStore.hpp>

namespace abyss::User
{
    class DBUserDataStore : public IUserDataStore
    {
        bool create() const final;
        s3d::Array<UserEntity> selectAll()const final;
        s3d::Optional<UserEntity> select(s3d::int32 userId)const final;

        void update(const UserEntity& entity)const final;
    };
}
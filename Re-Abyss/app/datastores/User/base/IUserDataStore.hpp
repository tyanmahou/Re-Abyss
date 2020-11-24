#pragma once
#include <abyss/entities/User/UserEntity.hpp>
#include <Siv3D/Array.hpp>
#include <Siv3D/Optional.hpp>

namespace abyss::User
{
    class IUserDataStore
    {
    public:
        virtual ~IUserDataStore() = default;

        virtual bool create() const = 0;
        virtual s3d::Array<UserEntity> selectAll()const = 0;
        virtual s3d::Optional<UserEntity> select(s3d::int32 userId)const = 0;

        virtual bool update(const UserEntity& entity)const = 0;
        virtual bool erase(s3d::int32 userId)const = 0;
    };
}
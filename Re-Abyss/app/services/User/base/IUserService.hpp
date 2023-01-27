#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/values/UserPlayMode.hpp>
#include <Siv3D/Fwd.hpp>
#include <Siv3D/HashTable.hpp>

namespace abyss::User
{
    class IUserService
    {
    public:
        virtual ~IUserService() = default;

        virtual s3d::HashTable<s3d::int32, UserModel> getUsers() const = 0;
        virtual UserModel create(s3d::int32 userId, UserPlayMode playMode = UserPlayMode::Normal) const = 0;
        virtual UserModel login(const UserModel& user) const = 0;
        virtual UserModel save(const UserModel& user) const = 0;

        virtual bool erase(s3d::int32 userId) const = 0;
    };
}

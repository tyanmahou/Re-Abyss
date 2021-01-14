#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/types/UserPlayMode.hpp>
#include <Siv3D/Fwd.hpp>
#include <Siv3D/Array.hpp>

namespace abyss::User
{
    class IUserService
    {
    public:
        virtual ~IUserService() = default;

        virtual s3d::Array<UserModel> getUsers() const = 0;
        virtual UserModel create(s3d::int32 userId, UserPlayMode playMode = UserPlayMode::Normal) const = 0;
    };
}
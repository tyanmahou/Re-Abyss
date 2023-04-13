#pragma once
#include <abyss/models/User/UserModel.hpp>
#include <Siv3D/Optional.hpp>

namespace abyss::User
{
    class StorageData
    {
        s3d::Optional<UserModel> currentUser;
    };
}

#pragma once
#include <abyss/modules/User/UserData.hpp>
#include <Siv3D/Optional.hpp>

namespace abyss::User
{
    class RuntimeData
    {
    public:
        s3d::Optional<UserData> currentUser;
    };
}

#pragma once
#include <Siv3D/Fwd.hpp>
#include <Siv3D/String.hpp>
#include <Siv3D/DateTime.hpp>

#include <abyss/types/UserPlayMode.hpp>

namespace abyss::User
{
    struct UserEntity
    {
        s3d::int32 userId;
        UserPlayMode playMode;
        s3d::DateTime created_at;
    };
}
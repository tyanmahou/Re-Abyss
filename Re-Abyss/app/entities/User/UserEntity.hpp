#pragma once
#include <Siv3D/Fwd.hpp>
#include <Siv3D/String.hpp>
#include <Siv3D/DateTime.hpp>

#include <abyss/types/UserPlayMode.hpp>

namespace abyss::User
{
    struct UserEntity
    {
        // ユーザーID
        s3d::int32 userId;
        // プレイモード
        UserPlayMode playMode;
        // プレイ時間
        s3d::Duration playTime;
        // 作成日
        s3d::DateTime createdAt;
    };
}
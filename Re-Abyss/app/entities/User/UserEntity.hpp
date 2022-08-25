#pragma once
#include <Siv3D/Fwd.hpp>
#include <Siv3D/String.hpp>
#include <Siv3D/DateTime.hpp>

#include <abyss/entities/OopartsType.hpp>
#include <abyss/entities/UserPlayMode.hpp>
#include <abyss/utils/DB/DBBindDef.hpp>

namespace abyss::User
{
    struct UserEntity
    {
        // ユーザーID
        [[DB_COLUMN(userId, "user_id")]]
        s3d::int32 userId;
        // プレイモード
        [[DB_COLUMN(playMode, "play_mode")]]
        UserPlayMode playMode;
        // プレイ時間
        [[DB_COLUMN(playTime, "play_time")]]
        s3d::Duration playTime;
        // 更新日
        [[DB_COLUMN(updatedAt, "updated_at")]]
        s3d::DateTime updatedAt;
        // 作成日
        [[DB_COLUMN(createdAt, "created_at")]]
        s3d::DateTime createdAt;
    };
}

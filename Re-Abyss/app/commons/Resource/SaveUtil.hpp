#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/values/UserPlayMode.hpp>
#include <Siv3DSQL.hpp>

namespace abyss::Resource::UserData
{
    class Storage;
}
namespace abyss::Resource::SaveUtil
{
    [[nodiscard]] s3dsql::SQLite3 DB();

    /// <summary>
    /// ユーザーの生成
    /// </summary>
    User::UserModel CreateUser(s3d::int32 userId, UserPlayMode playMode);

    /// <summary>
    /// ユーザーの削除
    /// </summary>
    bool EraseUser(s3d::int32 userId);

    /// <summary>
    /// ログイン
    /// </summary>
    User::UserModel Login(const User::UserModel& user);

    /// <summary>
    /// ユーザーの保存
    /// </summary>
    User::UserModel SaveUser(const User::UserModel& user);
}

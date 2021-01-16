#pragma once
#include <abyss/commons/Fwd.hpp>
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
    User::UserModel CreateUser(s3d::int32 userId);

    /// <summary>
    /// ユーザーの削除
    /// </summary>
    bool EraseUser(s3d::int32 userId);

    /// <summary>
    /// ログイン
    /// </summary>
    User::UserModel Login(const User::UserModel& user);
}
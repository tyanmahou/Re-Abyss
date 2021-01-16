#pragma once
#include <Siv3DSQL.hpp>

namespace abyss::Resource::UserData
{
    class Storage;
}
namespace abyss::Resource::SaveUtil
{
    [[nodiscard]] s3dsql::SQLite3 DB();

    bool EraseUser(s3d::int32 userId);
}
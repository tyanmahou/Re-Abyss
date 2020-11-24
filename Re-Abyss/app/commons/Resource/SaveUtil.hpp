#pragma once
#include <Siv3DSQL.hpp>

namespace abyss::Resource::SaveUtil
{
    [[nodiscard]] s3dsql::SQLite3 DB();
}
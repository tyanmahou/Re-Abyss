#pragma once
#include <abyss/utils/JSON/JSONUtil.hpp>

namespace abyss::Network::GitHub::Issue
{
    /// <summary>
    /// GitHub Issue
    /// </summary>
    struct Issue
    {
        [[JSON_BIND(id)]]
        s3d::int32 id;

        [[JSON_BIND(number)]]
        s3d::int32 number;

        [[JSON_BIND(title)]]
        s3d::String title;

        [[JSON_BIND(url)]]
        s3d::String url;
    };

    using IssueList = s3d::Array<Issue>;
}

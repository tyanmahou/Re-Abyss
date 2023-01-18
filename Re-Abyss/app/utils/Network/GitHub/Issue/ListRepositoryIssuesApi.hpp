#pragma once
#include <abyss/utils/Network/GItHub/BaseApi.hpp>
#include <abyss/utils/Network/GItHub/Issue/Issue.hpp>

namespace abyss::Network::GitHub::Issue
{
    class ListRepositoryIssuesApi
    {
    public:
        static constexpr auto* Url = U"https://api.github.com/repos/{}/{}/issues";
        using Response = IssueList;
    public:
        static ApiResponse<Response> Request(
            const s3d::String& owner,
            const s3d::String& repo,
            const s3d::String& token
        );
    };
}

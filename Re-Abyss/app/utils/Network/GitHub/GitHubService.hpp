#pragma once
#include <Siv3D/String.hpp>
#include <abyss/utils/Network/GitHub/Issue/ListRepositoryIssuesApi.hpp>

namespace abyss::Network::GitHub
{
    class GitHubService
    {
    public:

        static ApiResponse<Issue::ListRepositoryIssuesApi::Response> ListRepositoryIssues(
            const s3d::String& owner,
            const s3d::String& repo,
            const s3d::String& token
        );

        /// <summary>
        /// ブラウザでイシューを開く
        /// </summary>
        /// <param name="owner"></param>
        /// <param name="repo"></param>
        /// <param name="number"></param>
        /// <returns></returns>
        static bool OpenIssueByBrowser(
            const s3d::String& owner,
            const s3d::String& repo,
            const s3d::int32 number
        );
    };
}

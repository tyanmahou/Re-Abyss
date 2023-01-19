#include <abyss/utils/Network/GitHub/GitHubService.hpp>
#include <abyss/utils/Network/GitHub/Issue/ListRepositoryIssuesApi.hpp>
#include <abyss/utils/Network/GitHub/GraphQL/GraphQLApi.hpp>
#include <Siv3D.hpp>

namespace abyss::Network::GitHub
{
    s3d::JSON GitHubService::GraphQL(const s3d::String& query, const s3d::String& token)
    {
        return GraphQL::GraphQLApi::Request(query, token);
    }
    ApiResponse<Issue::ListRepositoryIssuesApi::Response> GitHubService::ListRepositoryIssues(const s3d::String& owner, const s3d::String& repo, const s3d::String& token)
    {
        return Issue::ListRepositoryIssuesApi::Request(owner, repo, token);
    }
    bool GitHubService::OpenIssueByBrowser(const s3d::String& owner, const s3d::String& repo, const s3d::int32 number)
    {
        return System::LaunchBrowser(U"https://github.com/{}/{}/issues/{}"_fmt(owner, repo, number));
    }
}

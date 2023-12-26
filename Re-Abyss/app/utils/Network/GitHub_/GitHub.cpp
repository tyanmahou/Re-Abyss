#include <abyss/utils/Network/GitHub/GitHub.hpp>
#include <abyss/utils/Network/GitHub/Issue/ListRepositoryIssuesApi.hpp>
#include <abyss/utils/Network/GitHub/GraphQL/GraphQLApi.hpp>
#include <Siv3D.hpp>

namespace abyss::Network::GitHub
{
    s3d::JSON GitHub::GraphQL(const s3d::String& query, const s3d::String& token)
    {
        return GraphQL::GraphQLApi::Request(query, token);
    }
    ApiResponse<Issue::ListRepositoryIssuesApi::Response> GitHub::ListRepositoryIssues(const s3d::String& owner, const s3d::String& repo, const s3d::String& token)
    {
        return Issue::ListRepositoryIssuesApi::Request(owner, repo, token);
    }
    bool GitHub::OpenIssueByBrowser(const s3d::String& owner, const s3d::String& repo, const s3d::int32 number)
    {
        return System::LaunchBrowser(U"https://github.com/{}/{}/issues/{}"_fmt(owner, repo, number));
    }
}

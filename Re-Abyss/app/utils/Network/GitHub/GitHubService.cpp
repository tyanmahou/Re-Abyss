#include <abyss/utils/Network/GitHub/GitHubService.hpp>
#include <abyss/utils/Network/GitHub/Issue/ListRepositoryIssuesApi.hpp>
#include <Siv3D.hpp>

namespace abyss::Network::GitHub
{
    ApiResponse<Issue::ListRepositoryIssuesApi::Response> GitHubService::ListRepositoryIssues(const s3d::String& owner, const s3d::String& repo, const s3d::String& token)
    {
        return Issue::ListRepositoryIssuesApi::Request(owner, repo, token);
    }
    bool GitHubService::OpenIssueByBrowser(const s3d::String& owner, const s3d::String& repo, const s3d::int32 number)
    {
        return System::LaunchBrowser(U"https://github.com/{}/{}/issues/{}"_fmt(owner, repo, number));
    }
}

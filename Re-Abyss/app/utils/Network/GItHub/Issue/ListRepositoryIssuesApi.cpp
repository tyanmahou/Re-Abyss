#include <abyss/utils/Network/GItHub/Issue/ListRepositoryIssuesApi.hpp>

namespace abyss::Network::GitHub::Issue
{
    ApiResponse<ListRepositoryIssuesApi::Response> ListRepositoryIssuesApi::Request(
        const s3d::String& owner,
        const s3d::String& repo,
        const s3d::String& token
    )
    {
        return GetTo<Response>(s3d::Format(Url, owner, repo), token);
    }
}

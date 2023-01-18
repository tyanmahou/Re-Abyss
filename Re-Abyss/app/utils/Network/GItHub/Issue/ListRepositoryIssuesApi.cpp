#include <abyss/utils/Network/GitHub/Issue/ListRepositoryIssuesApi.hpp>

namespace abyss::Network::GitHub::Issue
{
    ApiResponse<ListRepositoryIssuesApi::Response> ListRepositoryIssuesApi::Request(
        const s3d::String& owner,
        const s3d::String& repo,
        const s3d::String& token
    )
    {
        return BaseApi::GetTo<Response>(s3d::Fmt(Url)(owner, repo), token);
    }
}

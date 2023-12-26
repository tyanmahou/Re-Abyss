#include <abyss/utils/Network/GitHub/GraphQL/GraphQLApi.hpp>
#include <abyss/utils/Network/GitHub/base/BaseApi.hpp>

namespace abyss::Network::GitHub::GraphQL
{
    s3d::JSON GraphQLApi::Request(const s3d::String& query, const s3d::String& token)
    {
        JSON request;
        request[U"query"] = query;
        return BaseApi::Post(Url, token, request).value_or(s3d::JSON::Invalid());
    }
}


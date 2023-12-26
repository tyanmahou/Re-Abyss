#pragma once
#include <Siv3D/JSON.hpp>

namespace abyss::Network::GitHub::GraphQL
{
    class GraphQLApi
    {
    public:
        static constexpr auto* Url = U"https://api.github.com/graphql";
    public:

        static s3d::JSON Request(const s3d::String& query, const s3d::String& token);
    };
}

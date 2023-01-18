#pragma once
#include <expected>
#include <abyss/utils/JSON/JSONUtil.hpp>

namespace abyss::Network::GitHub
{
    template<class T>
    using ApiResponse = std::expected<T, s3d::int32>;

    class BaseApi
    {
    public:
        static ApiResponse<s3d::JSON> Get(
            const s3d::String& url,
            const s3d::String& token
        );

        template<class T>
        static ApiResponse<T> GetTo(
            const s3d::String& url,
            const s3d::String& token
        ) {
            auto result = Get(url, token);
            if (!result.has_value()) {
                return std::unexpected(result.error());
            }
            return JSONUtil::FromJSON<T>(result.value());
        }
    };
}

#pragma once
#include <abyss/utils/Network/GitHub/base/ApiResponse.hpp>
#include <abyss/utils/JSON/JSONUtil.hpp>

namespace abyss::Network::GitHub
{
    class BaseApi
    {
    public:
        static ApiResponse<s3d::JSON> Get(
            const s3d::String& url,
            const s3d::String& token
        );
        static ApiResponse<s3d::JSON> Post(
            const s3d::String& url,
            const s3d::String& token,
            const s3d::JSON& param
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

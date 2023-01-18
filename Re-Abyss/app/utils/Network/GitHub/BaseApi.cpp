#include <abyss/utils/Network/GItHub/BaseApi.hpp>

namespace abyss::Network::GitHub
{
    ApiResponse<s3d::JSON> BaseApi::Get(const s3d::String& url, const s3d::String& token)
    {
        MemoryWriter writer;
        auto result = s3d::SimpleHTTP::Get(
            url,
           {
                {U"User-Agent", U"Awesome-Octocat-App"},
                {U"Accept", U"application/vnd.github+json"},
                {U"Authorization", U"Bearer {}"_fmt(token)},
                {U"X-GitHub-Api-Version", U"2022-11-28"}
            }, writer);
        if (result.isOK()) {
            return s3d::JSON::Load(MemoryReader(writer.getBlob()));
        } else {
            return std::unexpected(static_cast<s3d::int32>(result.getStatusCode()));
        }
    }
}

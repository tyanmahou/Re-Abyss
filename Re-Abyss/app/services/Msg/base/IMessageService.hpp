#pragma once
#include <Siv3D/Array.hpp>
#include <Siv3D/String.hpp>

namespace abyss::Resource::Msg
{
    class IMessageService
    {
    public:
        virtual ~IMessageService() = default;

        virtual s3d::Array<std::pair<s3d::String, s3d::String>> getMessages(s3d::StringView category) const = 0;
    };
}

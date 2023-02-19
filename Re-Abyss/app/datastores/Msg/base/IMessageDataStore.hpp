#pragma once
#include <Siv3D/Array.hpp>
#include <Siv3D/String.hpp>
#include <abyss/commons/Resource/Msg/Language.hpp>

namespace abyss::Resource::Msg
{
    class IMessageDataStore
    {
    public:
        virtual ~IMessageDataStore() = default;

        virtual s3d::Array<std::pair<s3d::String, s3d::String>> select(s3d::StringView category, const Language& lang) const = 0;
    };
}

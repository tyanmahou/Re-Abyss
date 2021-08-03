#pragma once
#include <Siv3D/Color.hpp>

namespace abyss::Attribute
{
    class IAttributeDataStore
    {
    public:
        virtual ~IAttributeDataStore() = default;

        virtual s3d::Color getBgColor() const = 0;
    };
}